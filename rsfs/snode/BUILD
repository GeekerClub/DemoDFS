cc_library(
    name = 'snode_impl',
    srcs = 'snode_impl.cc',
    deps = [
        '//rsfs/proto:snode_info_proto',
        '//rsfs/proto:proto_helper',
        '//rsfs/master:master_client',
        '//rsfs:rsfs_flags',
    ]
)

cc_library(
    name = 'sode_client',
    srcs = 'snode_client.cc',
    deps = [
        '//rsfs/proto:snode_rpc_proto',
        '//rsfs:rpc_client'
    ]
)

cc_library(
    name = 'remote_snode',
    srcs = 'remote_snode.cc',
    deps = [
        ':snode_impl',
        '//rsfs:rpc_server',
        '//rsfs:rsfs_flags',
        '//rsfs/proto:snode_rpc_proto'
    ]
)

cc_library(
    name = 'snode_entry',
    srcs = 'snode_entry.cc',
    deps = [
        ':snode_impl',
        '//rsfs/utils:memory_tool',
        '//rsfs/utils:utils_cmd',
        '//rsfs:rsfs_entry',
    ]
)
