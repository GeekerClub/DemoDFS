cc_library(
    name = 'rsfs_counters',
    srcs = 'rsfs_counters.cc',
    deps = [
        '//toft/container:counter'
    ]
)

cc_library(
    name = 'rsfs_flags',
    srcs = 'rsfs_flags.cc',
)

cc_library(
    name = 'rpc_client',
    srcs = 'rpc_client.cc',
    deps = [
        '//rsfs/utils:ip_address',
        '//toft/system/threading:threading',
        '//trident:trident',
        '//thirdparty/gflags:gflags',
        '//thirdparty/glog:glog'
    ]
)

cc_library(
    name = 'rpc_server',
    srcs = 'rpc_server.cc',
    deps = [
        '//rsfs/utils:ip_address',
        '//toft/system/timer:timer',
        '//trident:trident',
        '//thirdparty/gflags:gflags',
        '//thirdparty/glog:glog'
    ]
)

cc_library(
    name = 'rsfs_entry',
    srcs = 'rsfs_entry.cc',
    deps = [
        '//toft/system/threading:threading'
    ]
)

cc_binary(
    name = 'rsfs_main',
    srcs = 'rsfs_main.cc',
    deps = [
        '//rsfs/master:master_entry',
        '//rsfs/snode:snode_entry',
        '//rsfs/utils:utils_cmd',
        '//rsfs:rsfs_flags',
        '//rsfs:rsfs_counters',
        '//thirdparty/gflags:gflags',
        '//thirdparty/glog:glog',
        '//toft/storage/file:afs_fs',
        '//toft/storage/file:file',
        '//toft/storage/file:hdfs_fs'
    ]
)

cc_library(
    name = 'http_server',
    srcs = 'http_server.cc',
    deps = [
        '//rsfs/utils:ip_address',
        '//toft/net/mime:mime',
        '//toft/system/threading:threading',
        '//trident:trident',
        '//thirdparty/gflags:gflags',
        '//thirdparty/glog:glog'
    ]
)

cc_test(
    name = 'http_server_test',
    srcs = 'http_server_test.cc',
    deps = [
        ':http_server'
    ]
)

