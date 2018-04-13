// Copyright (C) 2016, For toft authors.
// Author: Xiang Zhang (zhangxiang.gk@gmail.com)
//
// Description:

#include "thirdparty/gtest/gtest.h"

#include "http_server.h"

namespace rsfs {

TEST(HttpServerTest, StartAndStopServer) {
    HttpServer http_server("127.0.0.1", 8542);

    EXPECT_FALSE(http_server.StopServer());
    EXPECT_TRUE(http_server.StartServer());
    EXPECT_TRUE(http_server.StopServer());
}

TEST(HttpServerImplTest, StaticResourceHandler) {
    HttpServerImpl http_server_impl("127.0.0.1", 8542);
    http_server_impl.RegisterStaticResource("/exist.js", "test");
    trident::HTTPRequest request;
    trident::HTTPResponse response;
    request.type = trident::HTTPRequest::GET;
    request.path = "/noexist.xxxxx";

    EXPECT_FALSE(http_server_impl.StaticResourceHandler(request, response));
    EXPECT_EQ("application/octet-stream", response.content_type);

    request.type = trident::HTTPRequest::GET;
    request.path = "/exist.js";
    EXPECT_TRUE(http_server_impl.StaticResourceHandler(request, response));
}

}  // namespace rsfs
