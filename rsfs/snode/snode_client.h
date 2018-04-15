// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (qinan@baidu.com)
//
// Description:
//


#ifndef RSFS_SNODE_SNODE_CLIENT_H
#define RSFS_SNODE_SNODE_CLIENT_H

#include "trident/pbrpc.h"

#include "rsfs/proto/snode_rpc.pb.h"
#include "rsfs/rpc_client.h"

DECLARE_int32(rsfs_stemnode_connect_retry_period);
DECLARE_int32(rsfs_stemnode_rpc_timeout_period);

class toft::ThreadPool;

namespace rsfs {
namespace snode {

class SNodeClient : public RpcClient<SNodeServer::Stub> {
public:
    static void SetThreadPool(toft::ThreadPool* thread_pool);

    static void SetRpcOption(int32_t max_inflow, int32_t max_outflow,
                             int32_t pending_buffer_size, int32_t thread_num);

    SNodeClient(const std::string& addr = "",
                   int32_t rpc_timeout = FLAGS_rsfs_stemnode_rpc_timeout_period);

    ~SNodeClient();

    bool OpenData(const OpenDataRequest* request,
                  OpenDataResponse* response,
                  toft::Closure<void
                                (OpenDataRequest*, OpenDataResponse*,
                                 bool, int)>* done = NULL);

    bool CloseData(const CloseDataRequest* request,
                          CloseDataResponse* response,
                          toft::Closure<void
                                        (CloseDataRequest*, CloseDataResponse*,
                                         bool, int)>* done = NULL);

    bool WriteData(const WriteDataRequest* request,
                          WriteDataResponse* response,
                          toft::Closure<void
                                        (WriteDataRequest*, WriteDataResponse*,
                                         bool, int)>* done = NULL);


    bool ReadData(const ReadDataRequest* request,
                          ReadDataResponse* response,
                          toft::Closure<void
                                        (ReadDataRequest*, ReadDataResponse*,
                                         bool, int)>* done = NULL);

private:
    bool IsRetryStatus(const StatusCode& status);

    int32_t m_rpc_timeout;
    static toft::ThreadPool* m_thread_pool;
};

} // namespace snode
} // namespace rsfs

#endif // RSFS_SNODE_SNODE_CLIENT_H
