// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#include "rsfs/master/master_entry.h"

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/glog/logging.h"

#include "rsfs/master/master_impl.h"
#include "rsfs/master/remote_master.h"
#include "rsfs/utils/ip_address.h"
#include "rsfs/utils/utils_cmd.h"

DECLARE_string(rsfs_master_addr);
DECLARE_string(rsfs_master_port);

namespace rsfs {
namespace master {


MasterEntry::MasterEntry()
    : m_master_impl(NULL),
      m_remote_master(NULL),
      m_rpc_server(NULL) {}

MasterEntry::~MasterEntry() {}

bool MasterEntry::StartServer() {
    std::string local_host_addr = utils::GetLocalHostAddr();
    IpAddress master_addr(local_host_addr, FLAGS_rsfs_master_port);
    FLAGS_rsfs_master_addr = master_addr.ToString();
    LOG(INFO) << "start master RPC server at: " << FLAGS_rsfs_master_addr;

    m_master_impl.reset(new MasterImpl());
    m_remote_master = new RemoteMaster(m_master_impl.get());

    if (!m_master_impl->Init()) {
        return false;
    }

    m_rpc_server.reset(new RpcServer(master_addr.GetIp(),
                                     master_addr.GetPort()));
    m_rpc_server->RegisterService(m_remote_master);
    if (!m_rpc_server->StartServer()) {
        LOG(ERROR) << "start RPC server error";
        return false;
    }


    LOG(INFO) << "finish starting master server";
    return true;
}

void MasterEntry::ShutdownServer() {
    m_rpc_server->StopServer();
}

} // namespace master
} // namespace rsfs
