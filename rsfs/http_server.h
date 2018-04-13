// Copyright (C) 2016, For toft authors.
// Author: Xiang Zhang (zhangxiang.gk@gmail.com)
//
// Description:

#ifndef GUNIR_HTTP_SERVER_H
#define GUNIR_HTTP_SERVER_H

#include <map>
#include <string>
#include <utility>
#include <google/protobuf/service.h>
#include "toft/base/scoped_ptr.h"
#include "toft/base/string/string_piece.h"
#include "toft/system/threading/base_thread.h"
#include "toft/system/threading/event.h"
#include "trident/pbrpc.h"
#include "rsfs/utils/ip_address.h"

namespace rsfs {

class HttpServerImpl;

class HttpServer : public toft::BaseThread {
public:
    HttpServer(const std::string& ip, const uint32_t& port);
    ~HttpServer();

    bool StartServer();

    bool StopServer();

    void RegisterWebServlet(const std::string& path, trident::Servlet servlet);

    void RegisterStaticResource(const std::string& path,
                                const toft::StringPiece& string_piece);

protected:
    void Entry();

private:
    toft::scoped_ptr<HttpServerImpl> m_server_impl;
};

class HttpServerImpl {
public:
    typedef std::map<std::string, toft::StringPiece> StaticResourceMap;
    typedef std::pair<std::string, toft::StringPiece> StaticResourceMapPair;
    HttpServerImpl(const std::string& ip, const uint32_t& port);
    ~HttpServerImpl();

    void RegisterStaticResource(const std::string& path,
                                const toft::StringPiece& string_piece);

    void RegisterWebServlet(const std::string& path, trident::Servlet servlet);

    void Loop();

    void LoopBreak();

    bool StaticResourceHandler(const trident::HTTPRequest& request,
                               trident::HTTPResponse& response);

private:
    volatile bool m_started;
    IpAddress m_address;
    toft::AutoResetEvent m_event;
    toft::scoped_ptr<trident::RpcServer> m_server;
    trident::RpcServerOptions m_options;
    StaticResourceMap m_static_resource_map;
};

}  // namespace rsfs

#endif  // GUNIR_HTTP_SERVER_H
