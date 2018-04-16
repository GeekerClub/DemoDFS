// Copyright (C) 2016, for GeekerClub authors.
// Author: Pengyu Sun (sunpengyu@nbjl.nankai.edu.cn)
//
// Description:

#ifndef  RSFS_UTILS_MEMORY_TOOL_H
#define  RSFS_UTILS_MEMORY_TOOL_H

#include <stdint.h>
#include <string>
#include <vector>


namespace rsfs {
namespace util {

void TryReleaseFreeMemory(bool idle);

}  // namespace util
}  // namespace rsfs

#endif  // RSFS_UTILS_MEMORY_TOOL_H
