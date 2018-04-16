cc_library(
    name = 'utils_cmd',
    srcs = [
        'utils_cmd.cc',
        'string_ext.cc'
    ],
    deps = [
        '//toft/base/string:string',
        '//toft/storage/path:path',
    ]
)

cc_library(
    name = 'ip_address',
    srcs = 'ip_address.cc',
    deps = [
        '//toft/base/string:string',
    ]
)

cc_library(
    name = 'memory_tool',
    srcs = 'memory_tool.cc',
    deps = [
        '//rsfs:rsfs_flags',
        '//thirdparty/gperftools-2.0/src:tcmalloc'
    ]
)
