// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//

#include "rsfs/snode/snode_client.h"

namespace rsfs {
namespace snode {

toft::ThreadPool* SNodeClient::m_thread_pool = NULL;

void SNodeClient::SetThreadPool(toft::ThreadPool* thread_pool) {
    m_thread_pool = thread_pool;
}

void SNodeClient::SetRpcOption(int32_t max_inflow, int32_t max_outflow,
                                int32_t pending_buffer_size, int32_t thread_num) {
    RpcClientBase::SetOption(max_inflow, max_outflow,
                             pending_buffer_size, thread_num);
}

SNodeClient::SNodeClient(const std::string& server_addr,
                           int32_t rpc_timeout)
    : RpcClient<SNodeServer::Stub>(server_addr),
      m_rpc_timeout(rpc_timeout) {}

SNodeClient::~SNodeClient() {}

bool SNodeClient::OpenData(const OpenDataRequest* request,
                                   OpenDataResponse* response,
                                   toft::Closure<void (OpenDataRequest*,
                                                       OpenDataResponse*, bool, int)>* done) {
    return SendMessageWithRetry(&SNodeServer::Stub::OpenData,
                                request, response, done, "OpenData",
                                m_rpc_timeout, m_thread_pool);
}

bool SNodeClient::CloseData(const CloseDataRequest* request,
                                      CloseDataResponse* response,
                                      toft::Closure<void (CloseDataRequest*,
                                                          CloseDataResponse*,
                                                          bool, int)>* done) {
    return SendMessageWithRetry(&SNodeServer::Stub::CloseData,
                                request, response, done, "CloseData",
                                m_rpc_timeout, m_thread_pool);
}

bool SNodeClient::WriteData(const WriteDataRequest* request,
                                      WriteDataResponse* response,
                                      toft::Closure<void (WriteDataRequest*,
                                                          WriteDataResponse*,
                                                          bool, int)>* done) {
    return SendMessageWithRetry(&SNodeServer::Stub::WriteData,
                                request, response, done, "WriteData",
                                m_rpc_timeout, m_thread_pool);
}

bool SNodeClient::IsRetryStatus(const StatusCode& status) {
    return (status == kSNodeNotInited
            || status == kSNodeIsBusy);
}

} // namespace snode
} // namespace rsfs
