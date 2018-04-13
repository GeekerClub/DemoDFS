// Copyright (C) 2016, For toft authors.
// Author: Xiang Zhang (zhangxiang.gk@gmail.com)
//
// Description:

#include "rsfs/http_server.h"

#include "toft/net/mime/mime.h"

DEFINE_string(rsfs_httpserver_log_level, "ERROR", "");

DEFINE_bool(rsfs_httpserver_traffic_limit_enabled, true, "");
DEFINE_int32(rsfs_httpserver_traffic_limit_max_inflow, 1,
             "max in-traffic bandwidth (in MB/s)");
DEFINE_int32(rsfs_httpserver_traffic_limit_max_outflow, 1,
             "max out-traffic bandwidth (in MB/s)");

DEFINE_int32(rsfs_httpserver_retry_times, 3,
             "the retry times when server meets exception");
DEFINE_int32(rsfs_httpserver_retry_period, 1000,
             "the retry period (in ms) between both retry operation");
DEFINE_int32(rsfs_httpserver_error_retry_times, 15,
             "the maximal retry times of same error");
DEFINE_int32(rsfs_httpserver_keep_alive_time, 1800,
             "the maximal interval (in sec) to keep idle connections");
DEFINE_int32(rsfs_httpserver_max_pending_buffer_size, 2,
             "max pending buffer size (in MB) for server");
DEFINE_int32(rsfs_httpserver_work_thread_num, 1, "");

namespace rsfs {

HttpServer::HttpServer(const std::string& ip, const uint32_t& port) {
    m_server_impl.reset(new HttpServerImpl(ip, port));
}

HttpServer::~HttpServer() {
    StopServer();
}

void HttpServer::Entry() {
    while (!IsStopRequested()) {
        m_server_impl->Loop();
    }
}

bool HttpServer::StartServer() {
    Start();
    return true;
}

bool HttpServer::StopServer() {
    m_server_impl->LoopBreak();
    SendStopRequest();
    if (IsJoinable()) {
        Join();
    } else {
        LOG(ERROR) << "rsfs http server is not started";
        return false;
    }
    return true;
}

void HttpServer::RegisterWebServlet(const std::string& path,
                                    trident::Servlet servlet) {
    m_server_impl->RegisterWebServlet(path, servlet);
}

void HttpServer::RegisterStaticResource(const std::string& path,
                                        const toft::StringPiece& string_piece) {
    m_server_impl->RegisterStaticResource(path, string_piece);
}

HttpServerImpl::HttpServerImpl(const std::string& ip, const uint32_t& port)
    : m_started(false),
      m_address(ip, port) {
    if (FLAGS_rsfs_httpserver_log_level == "NOTICE") {
        TRIDENT_SET_LOG_LEVEL(NOTICE);
    } else {
        TRIDENT_SET_LOG_LEVEL(ERROR);
    }

    if (FLAGS_rsfs_httpserver_traffic_limit_enabled) {
        m_options.max_throughput_in =
            FLAGS_rsfs_httpserver_traffic_limit_max_inflow;
        m_options.max_throughput_out =
            FLAGS_rsfs_httpserver_traffic_limit_max_outflow;
    }
    m_options.max_pending_buffer_size =
        FLAGS_rsfs_httpserver_max_pending_buffer_size;
    m_options.work_thread_num = FLAGS_rsfs_httpserver_work_thread_num;
    m_options.keep_alive_time = FLAGS_rsfs_httpserver_keep_alive_time;
    m_server.reset(new trident::RpcServer(m_options));

    LOG(INFO) << "http server is activated (max_inflow: "
        << m_options.max_throughput_in
        << " M/s, max_outflow: " << m_options.max_throughput_out
        << " M/s, keep_alive_time: " << m_options.keep_alive_time
        << " sec, max_pending_buffer_size: " << m_options.max_pending_buffer_size
        << " MB, work_thread_num: " << m_options.work_thread_num
        << ")";
}

HttpServerImpl::~HttpServerImpl() {}

bool HttpServerImpl::StaticResourceHandler(const trident::HTTPRequest& request,
                                           trident::HTTPResponse& response) {
    uint32_t rpos = request.path.rfind(".");
    std::string suffix = request.path.substr(rpos);
    toft::MimeType mime_type;
    bool ret = mime_type.FromFileExtension(suffix);

    if (true == ret) {
        response.content_type = mime_type.ToString();
    } else {
        response.content_type = "application/octet-stream";
    }

    StaticResourceMap::iterator iter = m_static_resource_map.find(request.path);

    if (iter == m_static_resource_map.end()) {
        return false;
    }

    return response.content->Append((iter->second).data(), (iter->second).size());
}

void HttpServerImpl::RegisterStaticResource(const std::string& path,
                                            const toft::StringPiece& string_piece) {
    std::pair<StaticResourceMap::iterator, bool> ret =
        m_static_resource_map.insert(StaticResourceMapPair(path, string_piece));
    if (ret.second == true) {
        trident::Servlet servlet =
            trident::NewPermanentExtClosure(this, &HttpServerImpl::StaticResourceHandler);
        m_server->RegisterWebServlet(path, servlet);
        LOG(INFO) << "register web servlet : " << path;
    } else {
        LOG(INFO) << "servlet already exist : " << path;
    }
}

void HttpServerImpl::RegisterWebServlet(const std::string& path,
                                        trident::Servlet servlet) {
    m_server->RegisterWebServlet(path, servlet);
}

void HttpServerImpl::Loop() {
    uint32_t wait_time = FLAGS_rsfs_httpserver_retry_period;
    for (int32_t retry = 0;
         !m_started && retry < FLAGS_rsfs_httpserver_retry_times;
         ++retry) {
        m_started = m_server->Start(m_address.ToString());
        if (!m_started) {
            toft::ThisThread::Sleep(wait_time);
            wait_time *= 2;
            LOG(WARNING) << "http server fail to start, retry = " << retry;
        }
    }
    CHECK(m_started) << ", fail to start http server";
    m_event.Wait();
}

void HttpServerImpl::LoopBreak() {
    m_server->Stop();
    m_event.Set();
}

}  // namespace rsfs
