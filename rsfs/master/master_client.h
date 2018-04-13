// Copyright (C) 2015, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//


#ifndef RSFS_MASTER_MASTER_CLIENT_H
#define RSFS_MASTER_MASTER_CLIENT_H

#include "trident/pbrpc.h"
#include "thirdparty/gflags/gflags.h"

#include "rsfs/proto/master_rpc.pb.h"
#include "rsfs/rpc_client.h"

DECLARE_string(rsfs_master_addr);
DECLARE_string(rsfs_master_port);

// DECLARE_int32(rsfs_master_connect_retry_period);
DECLARE_int32(rsfs_master_rpc_timeout_period);

class toft::ThreadPool;

namespace rsfs {
namespace master {

class MasterClient : public RpcClient<MasterServer::Stub> {
public:
    static void SetThreadPool(toft::ThreadPool* thread_pool);

    static void SetRpcOption(int32_t max_inflow, int32_t max_outflow,
                             int32_t pending_buffer_size, int32_t thread_num);

    MasterClient(const std::string& addr = (FLAGS_rsfs_master_addr + ":" + FLAGS_rsfs_master_port),
                 int32_t rpc_timeout = FLAGS_rsfs_master_rpc_timeout_period);

    ~MasterClient();

    bool OpenFile(const OpenFileRequest* request,
                  OpenFileResponse* response,
                  toft::Closure<void
                                (OpenFileRequest*, OpenFileResponse*,
                                 bool, int)>* done = NULL);

    bool CloseFile(const CloseFileRequest* request,
                   CloseFileResponse* response,
                   toft::Closure<void
                              (CloseFileRequest*, CloseFileResponse*,
                               bool, int)>* done = NULL);

    bool ListFile(const ListFileRequest* request,
                  ListFileResponse* response,
                  toft::Closure<void
                              (ListFileRequest*, ListFileResponse*,
                               bool, int)>* done = NULL);

    bool Register(const RegisterRequest* request,
                  RegisterResponse* response,
                  toft::Closure<void
                                (RegisterRequest*, RegisterResponse*,
                                 bool, int)>* done = NULL);

    bool Report(const ReportRequest* request,
                ReportResponse* response,
                toft::Closure<void
                              (ReportRequest*, ReportResponse*,
                               bool, int)>* done = NULL);

private:
    bool IsRetryStatus(const StatusCode& status);

    int32_t m_rpc_timeout;
    static toft::ThreadPool* m_thread_pool;
};

} // namespace master
} // namespace rsfs

#endif // RSFS_MASTER_MASTER_CLIENT_H
