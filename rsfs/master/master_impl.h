// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//

#ifndef RSFS_MASTER_MASTER_IMPL_H
#define RSFS_MASTER_MASTER_IMPL_H

#include "toft/base/scoped_ptr.h"
#include "toft/system/threading/mutex.h"
#include "toft/system/threading/rwlock.h"
#include "toft/timer/timer_manager.h"

#include "rsfs/proto/master_rpc.pb.h"

namespace rsfs {
namespace master {

class NodeManager;
class MetaTree;

class MasterImpl {
public:
    enum MasterStatus {
        kNotInited = kMasterNotInited,
        kIsBusy = kMasterIsBusy,
        kIsRunning = kMasterIsRunning,
        kIsSecondary = kMasterIsSecondary,
        kIsReadonly = kMasterIsReadonly
    };

    MasterImpl();
    ~MasterImpl();

    bool Init();

    bool OpenFile(const OpenFileRequest* request,
                  OpenFileResponse* response);

    bool CloseFile(const CloseFileRequest* request,
                   CloseFileResponse* response);

    bool ListFile(const ListFileRequest* request,
                  ListFileResponse* response);

    bool Report(const ReportRequest* request,
                ReportResponse* response);

    bool Register(const RegisterRequest* request,
                  RegisterResponse* response);

private:
    bool OpenFileForRead(const OpenFileRequest* request,
                         OpenFileResponse* response);
    bool OpenFileForWrite(const OpenFileRequest* request,
                          OpenFileResponse* response);

private:
    mutable toft::RwLock m_status_mutex;
    MasterStatus m_status;

    mutable toft::RwLock m_rwlock;
    TimerManager m_timer_manager;

    toft::scoped_ptr<NodeManager> m_node_manager;
    toft::scoped_ptr<MetaTree> m_meta_tree;
};


} // namespace master
} // namespace rsfs

#endif // RSFS_MASTER_MASTER_IMPL_H
