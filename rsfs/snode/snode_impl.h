// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//

#ifndef RSFS_SNODE_SNODE_IMPL_H
#define RSFS_SNODE_SNODE_IMPL_H

#include "toft/base/scoped_ptr.h"
#include "toft/system/threading/event.h"
#include "toft/system/threading/mutex.h"
#include "toft/system/threading/thread_pool.h"

#include "rsfs/proto/snode_info.pb.h"
#include "rsfs/proto/snode_rpc.pb.h"
#include "rsfs/proto/status_code.pb.h"

namespace rsfs {

namespace master {
class MasterClient;
}

namespace snode {

class WorkerManager;

class SNodeImpl {
public:
    enum SNodeStatus {
        kNotInited = kSNodeNotInited,
        kIsIniting = kSNodeIsIniting,
        kIsBusy = kSNodeIsBusy,
        kRunning = kSNodeIsRunning
    };

    SNodeImpl(const SNodeInfo& node_info);
    ~SNodeImpl();

    bool Init();

    bool Exit();

    bool Register();

    bool Report();

    void TrigerReportByEvent();

    bool OpenData(const OpenDataRequest* request,
                       OpenDataResponse* response);

    bool CloseData(const CloseDataRequest* request,
                          CloseDataResponse* response);

    bool WriteData(const WriteDataRequest* request,
                          WriteDataResponse* response);

    bool IsIdle();

private:
    mutable toft::Mutex m_status_mutex;

    SNodeStatus m_status;
    uint64_t m_this_sequence_id;

    toft::scoped_ptr<master::MasterClient> m_master_client;
    toft::scoped_ptr<toft::ThreadPool> m_thread_pool;
    toft::AutoResetEvent m_report_event;
};


} // namespace snode
} // namespace rsfs

#endif // RSFS_SNODE_SNODE_IMPL_H
