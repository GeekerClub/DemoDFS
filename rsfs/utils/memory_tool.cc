// Copyright (C) 2016, for GeekerClub authors.
// Author: Pengyu Sun (sunpengyu@nbjl.nankai.edu.cn)
//
// Description:

#include "rsfs/utils/memory_tool.h"

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/glog/logging.h"
#include "thirdparty/perftools/malloc_extension.h"

DECLARE_uint64(rsfs_running_buffer_size);

namespace rsfs {
namespace util {

void TryReleaseFreeMemory(bool idle) {
    LOG(INFO) << "TryReleaseFreeMemory";
    size_t free_heap_bytes = 0;
    MallocExtension::instance()->GetNumericProperty("tcmalloc.pageheap_free_bytes",
                                                    &free_heap_bytes);
    if (free_heap_bytes == 0) {
        return;
    }
    if (idle == true || free_heap_bytes < FLAGS_rsfs_running_buffer_size * 1024 * 1024) {
        MallocExtension::instance()->ReleaseFreeMemory();
        VLOG(5) << "release buffer size: " << free_heap_bytes;
    } else {
        MallocExtension::instance()->ReleaseToSystem(free_heap_bytes / 2);
        VLOG(5) << "release buffer size: " << free_heap_bytes / 2;
    }
}

} // namespace util
} // namespace rsfs
