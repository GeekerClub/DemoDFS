// Copyright (C) 2015, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#include "rsfs/master/master_impl.h"

#include "thirdparty/gflags/gflags.h"
#include "toft/container/counter.h"

DECLARE_int32(rsfs_job_thread_min_num);
DECLARE_int32(rsfs_job_thread_max_num);
DECLARE_int64(rsfs_counter_reset_period);
DECLARE_string(rsfs_master_factory_type);

DECLARE_COUNTER(Rate, rsfs_query_counter);

namespace rsfs {
namespace master {


MasterImpl::MasterImpl() {
//     if (FLAGS_rsfs_master_factory_type == "default") {
//         m_factory.reset(new DefaultFactory());
//     } else {
//         m_factory.reset(new DefaultFactory());
//     }

    m_thread_pool.reset(new toft::ThreadPool(FLAGS_rsfs_job_thread_min_num,
                                             FLAGS_rsfs_job_thread_max_num));

}

MasterImpl::~MasterImpl() {
}

bool MasterImpl::Init() {
    toft::TimerManager::CallbackClosure* closure =
        toft::NewPermanentClosure(this, &MasterImpl::ResetCounters);
    m_timer_manager.AddPeriodTimer(FLAGS_rsfs_counter_reset_period, closure);
    return true;
}

bool MasterImpl::OpenFile(const OpenFileRequest* request,
                           OpenFileResponse* response) {
    LOG(INFO) << "rpc (OpenFile): " << request->ShortDebugString();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kMasterOk);
    return true;
}

bool MasterImpl::CloseFile(const CloseFileRequest* request,
                              CloseFileResponse* response) {
    LOG(INFO) << "rpc (CloseFile): " << request->ShortDebugString();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kMasterOk);
    VLOG(10) << "rpc (CloseFile) response: " << response->ShortDebugString();
    return true;
}

bool MasterImpl::ListFile(const ListFileRequest* request,
                             ListFileResponse* response) {
    LOG(INFO) << "rpc (ListFile): " << request->ShortDebugString();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kMasterOk);
    return true;
}

bool MasterImpl::Report(const ReportRequest* request,
                        ReportResponse* response) {
    VLOG(30) << "rpc report: " << request->ShortDebugString();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kMasterOk);
    return true;
}

bool MasterImpl::Register(const RegisterRequest* request,
                          RegisterResponse* response) {
    LOG(INFO) << "rpc register: " << request->ShortDebugString();
    response->set_sequence_id(request->sequence_id());
    response->set_status(kMasterOk);
    return true;
}

bool MasterImpl::GetJobJson(Json::Value* job_info_json) {
    Json::Value job_manager_json;
    (*job_info_json)["m_job_manager"] = job_manager_json;
    return true;
}


void MasterImpl::ResetCounters(uint64_t time_id) {
    std::string key;
    uint64_t value = 0;
//     int64_t timestamp = toft::GetTimestampInMs();

    COUNTER_rsfs_query_counter.GetAndReset(&value);
}


} // namespace master
} // namespace rsfs

