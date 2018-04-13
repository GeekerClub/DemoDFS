// Copyright (C) 2015, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//

#ifndef RSFS_MASTER_MASTER_IMPL_H
#define RSFS_MASTER_MASTER_IMPL_H

#include "thirdparty/jsoncpp/json.h"
#include "toft/base/scoped_ptr.h"
#include "toft/system/threading/mutex.h"
#include "toft/system/threading/rwlock.h"
#include "toft/system/threading/thread_pool.h"
#include "toft/system/timer/timer_manager.h"

#include "rsfs/proto/master_rpc.pb.h"

namespace rsfs {
namespace master {

class MasterImpl {
public:
    enum MasterStatus {
        kNotInited = kMasterNotInited,
        kIsBusy = kMasterIsBusy,
        kIsSecondary = kMasterIsSecondary,
        kIsReadonly = kMasterIsReadonly
    };

    MasterImpl();
    virtual ~MasterImpl();

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

    bool GetJobJson(Json::Value* job_info_json);

    void ResetCounters(uint64_t time_id);


private:
    mutable toft::Mutex m_status_mutex;
    MasterStatus m_status;

    mutable toft::RwLock m_rwlock;
    toft::TimerManager m_timer_manager;

    toft::scoped_ptr<toft::ThreadPool> m_thread_pool;
};


} // namespace master
} // namespace rsfs

#endif // RSFS_MASTER_MASTER_IMPL_H
