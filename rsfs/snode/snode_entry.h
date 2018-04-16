// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#ifndef RSFS_SNODE_SNODE_ENTRY_H
#define RSFS_SNODE_SNODE_ENTRY_H


#include "toft/base/scoped_ptr.h"

#include "rsfs/rsfs_entry.h"
#include "rsfs/rpc_server.h"

namespace rsfs {
namespace snode {

class SNodeImpl;
class RemoteSNode;

class SNodeEntry : public RsfsEntry {
public:
    SNodeEntry();
    ~SNodeEntry();

    bool StartServer();
    void ShutdownServer();
    bool Run();

// protected:
//     bool StartMonitor(const IpAddress& addr);
//     void ShutdownMonitor();

private:
    toft::scoped_ptr<SNodeImpl> m_snode_impl;
    RemoteSNode* m_remote_snode;
    toft::scoped_ptr<RpcServer> m_rpc_server;
};

} // namespace snode
} // namespace rsfs

#endif // RSFS_SNODE_SNODE_ENTRY_H
