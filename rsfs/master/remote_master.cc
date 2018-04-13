// Copyright (C) 2015, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#include "rsfs/master/remote_master.h"

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/glog/logging.h"
#include "toft/base/closure.h"
#include "toft/container/counter.h"

#include "rsfs/master/master_impl.h"

DECLARE_int32(rsfs_master_thread_min_num);
DECLARE_int32(rsfs_master_thread_max_num);

DECLARE_COUNTER(Rate, rsfs_query_counter);

namespace rsfs {
namespace master {


RemoteMaster::RemoteMaster(MasterImpl* master_impl)
    : m_master_impl(master_impl),
      m_thread_pool(new toft::ThreadPool(FLAGS_rsfs_master_thread_min_num,
                                   FLAGS_rsfs_master_thread_max_num)) {}

RemoteMaster::~RemoteMaster() {}

void RemoteMaster::OpenFile(google::protobuf::RpcController* controller,
                             const OpenFileRequest* request,
                             OpenFileResponse* response,
                             google::protobuf::Closure* done) {
    toft::Closure<void ()>* callback =
        toft::NewClosure(this, &RemoteMaster::DoOpenFile, controller,
                   request, response, done);
    m_thread_pool->AddTask(callback);

    COUNTER_rsfs_query_counter.AddCount();
}

void RemoteMaster::CloseFile(google::protobuf::RpcController* controller,
                                const CloseFileRequest* request,
                                CloseFileResponse* response,
                                google::protobuf::Closure* done) {
    toft::Closure<void ()>* callback =
        toft::NewClosure(this, &RemoteMaster::DoCloseFile, controller,
                   request, response, done);
    m_thread_pool->AddTask(callback);

    COUNTER_rsfs_query_counter.AddCount();
}

void RemoteMaster::ListFile(google::protobuf::RpcController* controller,
                               const ListFileRequest* request,
                               ListFileResponse* response,
                               google::protobuf::Closure* done) {
    toft::Closure<void ()>* callback =
        toft::NewClosure(this, &RemoteMaster::DoListFile, controller,
                   request, response, done);
    m_thread_pool->AddTask(callback);

    COUNTER_rsfs_query_counter.AddCount();
}


void RemoteMaster::Register(google::protobuf::RpcController* controller,
                            const RegisterRequest* request,
                            RegisterResponse* response,
                            google::protobuf::Closure* done) {
    toft::Closure<void ()>* callback =
        toft::NewClosure(this, &RemoteMaster::DoRegister, controller,
                   request, response, done);
    m_thread_pool->AddTask(callback);

    COUNTER_rsfs_query_counter.AddCount();
}

void RemoteMaster::Report(google::protobuf::RpcController* controller,
                          const ReportRequest* request,
                          ReportResponse* response,
                          google::protobuf::Closure* done) {
    toft::Closure<void ()>* callback =
        toft::NewClosure(this, &RemoteMaster::DoReport, controller,
                   request, response, done);
    m_thread_pool->AddTask(callback);

    COUNTER_rsfs_query_counter.AddCount();
}

// internal

void RemoteMaster::DoOpenFile(google::protobuf::RpcController* controller,
                              const OpenFileRequest* request,
                              OpenFileResponse* response,
                              google::protobuf::Closure* done) {
    LOG(INFO) << "accept RPC (OpenFile)";
    m_master_impl->OpenFile(request, response);
    LOG(INFO) << "finish RPC (OpenFile)";

    done->Run();
}

void RemoteMaster::DoCloseFile(google::protobuf::RpcController* controller,
                            const CloseFileRequest* request,
                            CloseFileResponse* response,
                            google::protobuf::Closure* done) {
    VLOG(30) << "accept RPC (CloseFile)";
    m_master_impl->CloseFile(request, response);
    VLOG(30) << "finish RPC (CloseFile)";

    done->Run();
}

void RemoteMaster::DoListFile(google::protobuf::RpcController* controller,
                            const ListFileRequest* request,
                            ListFileResponse* response,
                            google::protobuf::Closure* done) {
    LOG(INFO) << "accept RPC (ListFile)";
    m_master_impl->ListFile(request, response);
    LOG(INFO) << "finish RPC (ListFile)";

    done->Run();
}

void RemoteMaster::DoRegister(google::protobuf::RpcController* controller,
                              const RegisterRequest* request,
                              RegisterResponse* response,
                              google::protobuf::Closure* done) {
    LOG(INFO) << "accept RPC (Register)";
    m_master_impl->Register(request, response);
    LOG(INFO) << "finish RPC (Register)";

    done->Run();
}

void RemoteMaster::DoReport(google::protobuf::RpcController* controller,
                            const ReportRequest* request,
                            ReportResponse* response,
                            google::protobuf::Closure* done) {
    VLOG(30) << "accept RPC (Report)";
    m_master_impl->Report(request, response);
    VLOG(30) << "finish RPC (Report)";

    done->Run();
}


} // namespace master
} // namespace rsfs
