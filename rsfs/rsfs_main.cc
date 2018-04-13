// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#include <signal.h>

#include <iostream>

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/glog/logging.h"

#include "toft/base/binary_version.h"
#include "toft/base/scoped_ptr.h"

#include "rsfs/client/client_entry.h"
#include "rsfs/rsfs_entry.h"
#include "rsfs/leafnode/leafnode_entry.h"
#include "rsfs/stemnode/stemnode_entry.h"
#include "rsfs/master/master_entry.h"
#include "rsfs/utils/env_utils.h"

DECLARE_string(rsfs_role);

bool g_quit = false;

static void SignalIntHandler(int sig) {
    LOG(INFO) << "receive interrupt signal from user, will stop";
    g_quit = true;
}

rsfs::GunirEntry* SwitchGunirEntry() {
    const std::string& server_name = FLAGS_rsfs_role;

    if (server_name == "master") {
        return new rsfs::master::MasterEntry();
    } else if (server_name == "stemnode") {
        return new rsfs::stemnode::StemNodeEntry();
    } else if (server_name == "leafnode") {
        return new rsfs::leafnode::LeafNodeEntry();
    } else if (server_name == "client") {
        return new rsfs::client::ClientEntry();
    }
    LOG(ERROR) << "FLAGS_rsfs_role should be one of ("
        << "master | leafnode"
        << "), not : " << FLAGS_rsfs_role;
    return NULL;
}

int main(int argc, char** argv) {
    toft::SetupBinaryVersion();
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    ::google::InitGoogleLogging(argv[0]);

    rsfs::utils::SetupLog(FLAGS_rsfs_role);

    if (argc > 1) {
        std::string ext_cmd = argv[1];
        if (ext_cmd == "version" || ext_cmd == "-version"
            || ext_cmd == "--version") {
//             PrintSystemVersion();
            return 0;
        }
    }

    signal(SIGINT, SignalIntHandler);
    signal(SIGTERM, SignalIntHandler);

    toft::scoped_ptr<rsfs::GunirEntry> entry(SwitchGunirEntry());
    if (entry.get() == NULL) {
        return -1;
    }

    if (!entry->Start()) {
        return -1;
    }

    while (!g_quit) {
        if (!entry->Run()) {
            LOG(ERROR) << "Server run error ,and then exit now ";
            break;
        }
        signal(SIGINT, SignalIntHandler);
        signal(SIGTERM, SignalIntHandler);
    }

    if (!entry->Shutdown()) {
        return -1;
    }

    return 0;
}
