// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#include "rsfs/snode/snode_entry.h"

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/glog/logging.h"
#include "toft/system/threading/this_thread.h"

#include "rsfs/snode/snode_impl.h"
#include "rsfs/snode/remote_snode.h"
#include "rsfs/proto/snode_info.pb.h"
#include "rsfs/utils/utils_cmd.h"
#include "rsfs/utils/ip_address.h"
#include "rsfs/utils/memory_tool.h"

DECLARE_string(rsfs_snode_addr);
DECLARE_string(rsfs_snode_port);
DECLARE_string(rsfs_snode_monitor_port);
DECLARE_int64(rsfs_heartbeat_period);
DECLARE_int32(rsfs_snode_worker_thread_num);
DECLARE_bool(rsfs_monitor_enabled);

namespace rsfs {
namespace snode {


SNodeEntry::SNodeEntry()
    : m_snode_impl(NULL),
      m_remote_snode(NULL),
      m_rpc_server(NULL) {}

SNodeEntry::~SNodeEntry() {}

bool SNodeEntry::StartServer() {
    std::string local_host_addr = utils::GetLocalHostAddr();
    IpAddress snode_addr(local_host_addr, FLAGS_rsfs_snode_port);
    FLAGS_rsfs_snode_addr = snode_addr.ToString();
    LOG(INFO) << "start snode RPC server at: " << FLAGS_rsfs_snode_addr;

    SNodeInfo node_info;
    node_info.set_addr(snode_addr.ToString());
    node_info.set_status(kSNodeIsRunning);

    m_snode_impl.reset(new SNodeImpl(node_info));
    m_remote_snode = new RemoteSNode(m_snode_impl.get());

    if (!m_snode_impl->Init()) {
        return false;
    }

    m_rpc_server.reset(new RpcServer(snode_addr.GetIp(),
                                     snode_addr.GetPort()));
    m_rpc_server->RegisterService(m_remote_snode);
    if (!m_rpc_server->StartServer()) {
        LOG(ERROR) << "start RPC server error";
        return false;
    } else if (!m_snode_impl->Register()) {
        LOG(ERROR) << "fail to register to master";
        return false;
    }

//     if (!m_snode_impl->Init()) {
//         return false;
//     }

    LOG(INFO) << "finish starting snode server";
    return true;
}

void SNodeEntry::ShutdownServer() {
    m_rpc_server->StopServer();
    m_snode_impl.reset();
}

bool SNodeEntry::Run() {
    m_snode_impl->Report();
    util::TryReleaseFreeMemory(m_snode_impl->IsIdle());
    toft::ThisThread::Sleep(FLAGS_rsfs_heartbeat_period);
    return true;
}


} // namespace snode
} // namespace rsfs
