// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//


#ifndef RSFS_SNODE_BLOCK_MANAGER_H
#define RSFS_SNODE_BLOCK_MANAGER_H

#include <map>

#include "toft/file/file_stream.h"
#include "toft/system/threading/mutex.h"

namespace rsfs {
namespace snode {

class BlockStream {
public:
    enum Type {
        SEQ_READ = 1,
        RANDOM_READ = 2,
        APPEND = 3
    };
    BlockStream(FileStream* stream, Type type);
    ~BlockStream();

    FileStream* GetFileStream();
    Type GetType() const;

    int32_t AddRef();
    int32_t DecRef();
    int32_t GetRef() const;

private:
    mutable toft::RwLock m_mutex;
    FileStream* m_stream;

    Type m_type;
    int32_t m_ref_count;
};

class BlockManager {
public:
    BlockManager();
    ~BlockManager();

    bool NewBlockStream(uint64_t block_id, BlockStream::Type type);
    BlockStream* GetBlockStream(uint64_t block_id);
    bool AddBlockStream(uint64_t block_id, BlockStream* stream);
    bool RemoveBlockStream(uint64_t block_id);

private:
    mutable toft::RwLock m_mutex_list;
    std::map<uint64_t, BlockStream*> m_block_io;
};

} // namespace snode
} // namespace rsfs

#endif // RSFS_SNODE_BLOCK_MANAGER_H
