proto_library(
    name = 'status_code_proto',
    srcs = 'status_code.proto'
)

proto_library(
    name = 'snode_info_proto',
    srcs = 'snode_info.proto',
    deps = [
        ':status_code_proto'
    ]
)

proto_library(
    name = 'meta_tree_proto',
    srcs = 'meta_tree.proto',
    deps = [
        ':status_code_proto',
        ':snode_info_proto'
    ]
)


proto_library(
    name = 'master_rpc_proto',
    srcs = 'master_rpc.proto',
    deps = [
        ':status_code_proto',
        ':snode_info_proto',
        ':meta_tree_proto',
        '//trident:rpc_option_proto'
    ]
)

proto_library(
    name = 'snode_rpc_proto',
    srcs = 'snode_rpc.proto',
    deps = [
        ':status_code_proto',
        '//trident:rpc_option_proto'
    ]
)

cc_library(
    name = 'proto_helper',
    srcs = 'proto_helper.cc',
    deps = [
        ':status_code_proto'
    ]
)
