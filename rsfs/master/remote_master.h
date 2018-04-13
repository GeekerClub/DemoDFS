// Copyright (C) 2018, for GeekerClub authors..
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//

#ifndef RSFS_MASTER_REMOTE_MASTER_H
#define RSFS_MASTER_REMOTE_MASTER_H

#include "toft/base/scoped_ptr.h"
#include "toft/thread/thread_pool.h"

#include "rsfs/proto/master_rpc.pb.h"

namespace rsfs {
namespace master {

class MasterImpl;

class RemoteMaster : public MasterServer {
public:
    RemoteMaster(MasterImpl* master_impl);
    ~RemoteMaster();

    void OpenFile(google::protobuf::RpcController* controller,
                  const OpenFileRequest* request,
                  OpenFileResponse* response,
                  google::protobuf::Closure* done);

    void CloseFile(google::protobuf::RpcController* controller,
                   const CloseFileRequest* request,
                   CloseFileResponse* response,
                   google::protobuf::Closure* done);

    void ListFile(google::protobuf::RpcController* controller,
                   const ListFileRequest* request,
                   ListFileResponse* response,
                   google::protobuf::Closure* done);

    void Register(google::protobuf::RpcController* controller,
                  const RegisterRequest* request,
                  RegisterResponse* response,
                  google::protobuf::Closure* done);

    void Report(google::protobuf::RpcController* controller,
                const ReportRequest* request,
                ReportResponse* response,
                google::protobuf::Closure* done);

private:
    void DoOpenFile(google::protobuf::RpcController* controller,
                    const OpenFileRequest* request,
                    OpenFileResponse* response,
                    google::protobuf::Closure* done);

    void DoCloseFile(google::protobuf::RpcController* controller,
                     const CloseFileRequest* request,
                     CloseFileResponse* response,
                     google::protobuf::Closure* done);

    void DoListFile(google::protobuf::RpcController* controller,
                     const ListFileRequest* request,
                     ListFileResponse* response,
                     google::protobuf::Closure* done);

    void DoRegister(google::protobuf::RpcController* controller,
                    const RegisterRequest* request,
                    RegisterResponse* response,
                    google::protobuf::Closure* done);

    void DoReport(google::protobuf::RpcController* controller,
                  const ReportRequest* request,
                  ReportResponse* response,
                  google::protobuf::Closure* done);

private:
    MasterImpl* m_master_impl;
    toft::scoped_ptr<ThreadPool> m_thread_pool;
};


} // namespace master
} // namespace rsfs

#endif // RSFS_MASTER_REMOTE_MASTER_H
