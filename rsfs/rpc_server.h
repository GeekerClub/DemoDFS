// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#ifndef RSFS_RPC_SERVER_H
#define RSFS_RPC_SERVER_H

#include <string>
#include <google/protobuf/service.h>

#include "toft/base/scoped_ptr.h"
#include "toft/system/threading/base_thread.h"
#include "toft/system/threading/event.h"
#include "trident/rpc_server.h"

#include "rsfs/utils/ip_address.h"

namespace rsfs {

class RpcServerImpl {
public:
    RpcServerImpl() {}
    virtual ~RpcServerImpl() {}

    virtual void RegisterService(::google::protobuf::Service* service) = 0;
    virtual void Loop() = 0;
    virtual void LoopBreak() = 0;
};

class RpcServer : public toft::BaseThread {
public:
    RpcServer(const std::string& ip, uint32_t port);
    ~RpcServer();

    bool StartServer();

    bool StopServer();

    void RegisterService(::google::protobuf::Service* service);

protected:
    void Entry();

private:
    toft::scoped_ptr<RpcServerImpl> m_server_impl;
};


// Trident RPC server Implementation
// The design is flexible to switch to other Protobuf-based RPC framework

class RpcServerEventHandler : public trident::RpcServer::EventHandler {
public:
    RpcServerEventHandler();
    void NotifyAcceptFailed(trident::RpcErrorCode error_code,
                            const std::string& error_text);

private:
    uint32_t m_error_retry;
    int64_t m_error_previous_timestamp;
};

class RpcServerTrident : public RpcServerImpl {
public:
    RpcServerTrident(const std::string& ip, uint16_t port);
    ~RpcServerTrident();

    void RegisterService(::google::protobuf::Service* service);
    void Loop();
    void LoopBreak();

private:
    toft::AutoResetEvent m_event;
    IpAddress m_address;
    bool m_started;
    trident::RpcServerOptions m_options;
    toft::scoped_ptr<trident::RpcServer> m_server;

    RpcServerEventHandler* m_event_handler;
};

} // namespace rsfs

#endif // RSFS_RPC_SERVER_H
