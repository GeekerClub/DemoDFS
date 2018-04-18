cc_library(
    name = 'meta_tree',
    srcs = 'meta_tree.cc',
    deps = [
        '//rsfs/proto:status_code_proto',
        '//rsfs/proto:meta_tree_proto',
        '//rsfs/proto:master_rpc_proto',
        '//toft/system/threading:_sync_object',
        '//thirdparty/leveldb:leveldb'
    ]
)

cc_library(
    name = 'node_manager',
    srcs = [
        'node_manager.cc',
        'node_state.cc'
    ],
    deps = [
        '//rsfs/proto:status_code_proto',
        '//rsfs/proto:meta_tree_proto',
        '//rsfs/proto:master_rpc_proto',
    
    ]
)

cc_library(
    name = 'master_impl',
    srcs = [
        'master_impl.cc'
    ],
    deps = [
        ':meta_tree',
        ':node_manager',
        '//rsfs/proto:proto_helper',
        '//toft/system/timer:timer',
        '//thirdparty/jsoncpp:jsoncpp',
        '//toft/system/threading:threading'
    ]
)

cc_library(
    name = 'master_client',
    srcs = 'master_client.cc',
    deps = [
        '//rsfs/proto:master_rpc_proto',
        '//rsfs:rsfs_flags',
        '//rsfs:rpc_client'
    ]
)

cc_library(
    name = 'remote_master',
    srcs = 'remote_master.cc',
    deps = [
        ':master_impl',
        '//rsfs:rsfs_flags',
        '//rsfs:rpc_server'
    ]
)

cc_library(
    name = 'master_entry',
    srcs = 'master_entry.cc',
    deps = [
        ':master_impl',
        ':remote_master',
        '//rsfs/utils:memory_tool',
        '//rsfs/utils:utils_cmd',
        '//rsfs:rsfs_entry',
    ]
)
