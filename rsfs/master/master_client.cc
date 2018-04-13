// Copyright (C) 2015, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//

#include "rsfs/master/master_client.h"

namespace rsfs {
namespace master {

toft::ThreadPool* MasterClient::m_thread_pool = NULL;

void MasterClient::SetThreadPool(toft::ThreadPool* thread_pool) {
    m_thread_pool = thread_pool;
}

void MasterClient::SetRpcOption(int32_t max_inflow, int32_t max_outflow,
                                int32_t pending_buffer_size, int32_t thread_num) {
    RpcClientBase::SetOption(max_inflow, max_outflow,
                             pending_buffer_size, thread_num);
}

MasterClient::MasterClient(const std::string& server_addr,
                           int32_t rpc_timeout)
    : RpcClient<MasterServer::Stub>(server_addr),
      m_rpc_timeout(rpc_timeout) {}

MasterClient::~MasterClient() {}

bool MasterClient::OpenFile(const OpenFileRequest* request,
                            OpenFileResponse* response,
                            toft::Closure<void (OpenFileRequest*, OpenFileResponse*, bool, int)>* done) {
    return SendMessageWithRetry(&MasterServer::Stub::OpenFile,
                                request, response, done, "OpenFile",
                                m_rpc_timeout, m_thread_pool);
}

bool MasterClient::CloseFile(const CloseFileRequest* request,
                             CloseFileResponse* response,
                             toft::Closure<void (CloseFileRequest*, CloseFileResponse*, bool, int)>* done) {
    return SendMessageWithRetry(&MasterServer::Stub::CloseFile,
                                request, response, done, "CloseFile",
                                m_rpc_timeout, m_thread_pool);
}

bool MasterClient::ListFile(const ListFileRequest* request,
                            ListFileResponse* response,
                            toft::Closure<void (ListFileRequest*, ListFileResponse*, bool, int)>* done) {
    return SendMessageWithRetry(&MasterServer::Stub::ListFile,
                                request, response, done, "ListFile",
                                m_rpc_timeout, m_thread_pool);
}


bool MasterClient::Register(const RegisterRequest* request,
                            RegisterResponse* response,
                            toft::Closure<void (RegisterRequest*, RegisterResponse*, bool, int)>* done) {
    return SendMessageWithRetry(&MasterServer::Stub::Register,
                                request, response, done, "Register",
                                m_rpc_timeout, m_thread_pool);
}

bool MasterClient::Report(const ReportRequest* request,
                          ReportResponse* response,
                          toft::Closure<void (ReportRequest*, ReportResponse*, bool, int)>* done) {
    return SendMessageWithRetry(&MasterServer::Stub::Report,
                                request, response, done, "Report",
                                m_rpc_timeout, m_thread_pool);
}

bool MasterClient::IsRetryStatus(const StatusCode& status) {
    return (status == kMasterNotInited
            || status == kMasterIsBusy);
}

} // namespace master
} // namespace rsfs
