// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//


#include "rsfs/snode/snode_impl.h"

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/glog/logging.h"
#include "toft/system/threading/this_thread.h"

#include "rsfs/master/master_client.h"
#include "rsfs/proto/master_rpc.pb.h"
#include "rsfs/proto/proto_helper.h"
#include "rsfs/types.h"


DECLARE_int32(rsfs_snode_thread_min_num);
DECLARE_int32(rsfs_snode_thread_max_num);

DECLARE_int64(rsfs_heartbeat_period);
DECLARE_int64(rsfs_heartbeat_retry_period_factor);
DECLARE_int32(rsfs_heartbeat_retry_times);

namespace rsfs {
namespace snode {


SNodeImpl::SNodeImpl(const SNodeInfo& node_info)
    : m_status(kNotInited),
      m_this_sequence_id(kSequenceIDStart),
      m_master_client(new master::MasterClient()),
      m_thread_pool(new toft::ThreadPool(FLAGS_rsfs_snode_thread_min_num,
                                         FLAGS_rsfs_snode_thread_max_num)) {
    master::MasterClient::SetThreadPool(m_thread_pool.get());
    master::MasterClient::SetOption();

    toft::Closure<void ()>* callback =
        toft::NewClosure(this, &SNodeImpl::TrigerReportByEvent);
    m_thread_pool->AddTask(callback);
}

SNodeImpl::~SNodeImpl() {}

bool SNodeImpl::Init() {
    return true;
}

bool SNodeImpl::Exit() {
    return true;
}

bool SNodeImpl::Register() {
    LOG(INFO) << "register()";
    RegisterRequest request;
    RegisterResponse response;

    m_this_sequence_id = kSequenceIDStart;
    request.set_sequence_id(m_this_sequence_id);
//     request.mutable_server_info()->CopyFrom(m_server_info);

    if (!m_master_client->Register(&request, &response, NULL)) {
        LOG(ERROR) << "Rpc failed: register, status = "
            << StatusCodeToString(response.status());
        return false;
    }
    if (response.status() == kMasterOk) {
        LOG(INFO) << "register success: " << response.ShortDebugString();
//         m_server_info.set_status(kSNodeIsRunning);
        ++m_this_sequence_id;
        return true;
    }

    LOG(INFO) << "register fail: " << response.ShortDebugString();
    return false;
}

bool SNodeImpl::Report() {
    LOG(INFO) << "report()";
    ReportRequest request;
    request.set_sequence_id(m_this_sequence_id);
//     SNodeInfo* server_info = request.mutable_server_info();
//     server_info->set_addr(m_server_info.addr());
//     server_info->set_type(m_server_info.type());

    int32_t retry = 0;
    while (retry < FLAGS_rsfs_heartbeat_retry_times) {
        ReportResponse response;


        if (!m_master_client->Report(&request, &response, NULL)) {
            LOG(ERROR) << "Rpc failed: report, status = "
                << StatusCodeToString(response.status());
        } else if (response.status() == kMasterOk) {
            LOG(INFO) << "report success, response: "
                << response.ShortDebugString();
            if (response.sequence_id() != m_this_sequence_id) {
                LOG(WARNING) << "report is lost";
                m_this_sequence_id = response.sequence_id() + 1;
            } else {
                ++m_this_sequence_id;
            }

            return true;
        } else if (response.status() == kSNodeNotRegistered
                   || response.status() == kSNodeNotExist) {
            if (!Register()) {
                return false;
            }
            return true;
        } else {
            LOG(ERROR) << "report failed: " << response.DebugString();
            toft::ThisThread::Sleep(retry * FLAGS_rsfs_heartbeat_period *
                                    FLAGS_rsfs_heartbeat_retry_period_factor);
        }
        ++retry;
    }
    return true;
}

void SNodeImpl::TrigerReportByEvent() {
    m_report_event.Wait();
    Report();
    toft::Closure<void ()>* callback =
        toft::NewClosure(this, &SNodeImpl::TrigerReportByEvent);
    m_thread_pool->AddTask(callback);
}

bool SNodeImpl::IsIdle() {
    return false;
}

bool SNodeImpl::OpenData(const OpenDataRequest* request,
                                 OpenDataResponse* response) {
    LOG(INFO) << "rpc (OpenData): " << request->ShortDebugString();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kSNodeOk);
    return true;
}

bool SNodeImpl::CloseData(const CloseDataRequest* request,
                                    CloseDataResponse* response) {
    LOG(INFO) << "rpc (CloseData):"
        << " sequence_id: "<< request->sequence_id();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kSNodeOk);
    return true;
}

bool SNodeImpl::WriteData(const WriteDataRequest* request,
                                    WriteDataResponse* response) {
    LOG(INFO) << "rpc (WriteData): " << request->ShortDebugString();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kSNodeOk);
    return true;
}

} // namespace snode
} // namespace rsfs
