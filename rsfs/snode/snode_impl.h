// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#ifndef RSFS_SNODE_SNODE_IMPL_H
#define RSFS_SNODE_SNODE_IMPL_H

#include "toft/base/closure.h"
#include "toft/thread/thread_pool.h"

#include "rsfs/master/master_client.h"
#include "rsfs/proto/snode_info.pb.h"
#include "rsfs/proto/snode_rpc.pb.h"
#include "rsfs/proto/status_code.pb.h"

namespace rsfs {
namespace snode {

class BlockManager;
class BlockStream;

class SNodeImpl {
public:
    enum SNodeStatus {
        kNotInited = kSNodeNotInited,
        kIsIniting = kSNodeIsIniting,
        kIsBusy = kSNodeIsBusy,
        kIsRunning = kSNodeIsRunning
    };
    SNodeImpl(const SNodeInfo& snode_info,
              master::MasterClient* master_client);
    ~SNodeImpl();

    bool Init();

    bool Exit();

    bool Register();

    bool Report();

    void OpenData(const OpenDataRequest* request,
                  OpenDataResponse* response,
                  google::protobuf::Closure* done);

    void CloseData(const CloseDataRequest* request,
                  CloseDataResponse* response,
                  google::protobuf::Closure* done);

    void WriteData(const WriteDataRequest* request,
                   WriteDataResponse* response,
                   google::protobuf::Closure* done);

    void ReadData(const ReadDataRequest* request,
                   ReadDataResponse* response,
                   google::protobuf::Closure* done);

private:
    bool ReadDataSequencial(BlockStream* stream, uint64_t size,
                            ReadDataResponse* response);
    bool ReadDataRandom(BlockStream* stream, uint64_t size, uint64_t offset,
                        ReadDataResponse* response);

private:
    SNodeInfo m_snode_info;
    SNodeStatus m_status;
    uint64_t m_this_sequence_id;

    master::MasterClient* m_master_client;
    toft::scoped_ptr<BlockManager> m_block_manager;
    toft::scoped_ptr<ThreadPool> m_thread_pool;
};

} // namespace snode
} // namespace rsfs

#endif // RSFS_SNODE_SNODE_IMPL_H
