// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#ifndef RSFS_MASTER_MASTER_ENTRY_H
#define RSFS_MASTER_MASTER_ENTRY_H

#include "bobby/bobby_server.h"

#include "toft/base/scoped_ptr.h"
#include "rsfs/rsfs_entry.h"

namespace rsfs {
namespace master {

class MasterImpl;
class RemoteMaster;

class MasterEntry : public RsfsEntry {
public:
    MasterEntry();
    ~MasterEntry();

    bool StartServer();
    void ShutdownServer();

private:
    bool InitZKAdaptor();

private:
    toft::scoped_ptr<MasterImpl> m_master_impl;
    //toft::scoped_ptr<RemoteMaster> m_remote_master;
    RemoteMaster* m_remote_master;
    toft::scoped_ptr<bobby::BobbyServer> m_bobby_server;
};

} // namespace master
} // namespace rsfs

#endif // RSFS_MASTER_MASTER_ENTRY_H
