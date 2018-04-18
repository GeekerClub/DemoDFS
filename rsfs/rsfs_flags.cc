// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:
//

#include <stdint.h>
#include "thirdparty/gflags/gflags.h"

/////////// common //////////
DEFINE_string(rsfs_user_identity, "", "the identity for user to be executed");

DEFINE_string(rsfs_role, "", "the role for binary to be executed");
DEFINE_int64(rsfs_counter_reset_period, 1000, "");
DEFINE_int64(rsfs_heartbeat_period, 3000, "");
DEFINE_int64(rsfs_heartbeat_retry_period_factor, 1, "");
DEFINE_int32(rsfs_heartbeat_retry_times, 5, "");

DEFINE_int32(rsfs_heartbeat_timeout_period_factor, 10, "");
DEFINE_int64(rsfs_job_result_size_limit, 64*1024*1024, "");

DEFINE_int64(rsfs_blocking_queue_time, 1000, "");
DEFINE_bool(rsfs_monitor_enabled, true, "");

DEFINE_uint64(rsfs_running_buffer_size, 1024, "release memory threshold in MB");

////////// comipler /////////

DEFINE_string(rsfs_planner_mode, "parallel",
              "the planner modle: simple|parallel");
DEFINE_int32(rsfs_compiler_inter_plan_limit, 10,
             "limit of inter tasks that report to one inter");
DEFINE_int32(rsfs_compiler_leaf_plan_limit, 1000,
             "limit of leaf tasks that report to one inter");

/////////  io  /////////

DEFINE_string(rsfs_default_charset_encoding, "UTF-8",
              "tablet data storage using charset encoding");
DEFINE_string(rsfs_job_cache_dir, "./job_cache/",
              "inter server's job cache dir ");
DEFINE_string(rsfs_query_output_dir, "./output/",
              "user recieve the query output in this dir");
DEFINE_uint64(rsfs_tablet_file_size, 64 * 1024 * 1024, "used for mempool and dump logic.");
DEFINE_uint64(rsfs_max_record_size, 32 * 1024 * 1024, "for block serialization.");
DEFINE_string(rsfs_csv_delim, ",", "CSV separated char, default Comma");
DEFINE_string(rsfs_path_delim, ";", "separated char for input path list, default Semicolon");
DEFINE_string(rsfs_temp_file_prefix, "temp_", "prefix of temporary tablet");
DEFINE_bool(rsfs_rename_temp_file_after_dump_enabled, false,
            "rename temp filename after dump");

//////////  master //////////
DEFINE_string(rsfs_master_addr, "127.0.0.1", "");
DEFINE_string(rsfs_master_port, "10000", "");
DEFINE_string(rsfs_master_monitor_port, "8110", "");
DEFINE_string(rsfs_master_factory_type, "default", "default | cluster");

DEFINE_int32(rsfs_master_connect_retry_period, 1000, "");
DEFINE_int32(rsfs_master_rpc_timeout_period, 5000, "");
DEFINE_int32(rsfs_master_thread_min_num, 1, "");
DEFINE_int32(rsfs_master_thread_max_num, 10, "");

DEFINE_int64(rsfs_remove_job_waiting_time, 3000, "");
DEFINE_int64(rsfs_remove_timeout_job_waiting_time, 10 * 60 * 1000, "In ms. Cancel timeout job");

DEFINE_string(rsfs_master_meta_dir, "./rsfs_meta", "the location of persistent storage");
DEFINE_string(rsfs_master_meta_table, "table_meta", "the location name of table meta");
DEFINE_string(rsfs_master_history_dir, "rsfs_history", "");
DEFINE_string(rsfs_master_history_table, "history_table", "");

DEFINE_int32(rsfs_table_thread_min_num, 1, "");
DEFINE_int32(rsfs_table_thread_max_num, 10, "");

DEFINE_string(rsfs_job_scheduler, "fair", "scheduling strategy, within [fair | slot | balance]");
DEFINE_int32(rsfs_job_thread_min_num, 1, "");
DEFINE_int32(rsfs_job_thread_max_num, 20, "");

DEFINE_int32(rsfs_master_emit_retry_times, 3, "");
DEFINE_int32(rsfs_master_emit_thread_min_num, 1, "");
DEFINE_int32(rsfs_master_emit_thread_max_num, 6, "");

// ip_condition_manager hold the current ms reports, which is a little longer
// than heartbeats
DEFINE_int64(rsfs_ip_condition_window, 4 * 1000, "");
// leaf fail rate use in master
DEFINE_double(rsfs_leaf_long_tail_start_percent, 0.8, "long tail inflection point");


//////////  snode //////////
DEFINE_string(rsfs_snode_addr, "127.0.0.1", "");
DEFINE_string(rsfs_snode_port, "10000", "");
DEFINE_string(rsfs_snode_monitor_port, "8210", "");

DEFINE_int32(rsfs_snode_connect_retry_period, 1000, "");
DEFINE_int32(rsfs_snode_rpc_timeout_period, 5000, "");
DEFINE_int32(rsfs_snode_thread_min_num, 1, "");
DEFINE_int32(rsfs_snode_thread_max_num, 10, "");

DEFINE_int64(rsfs_snode_result_memory_limit, 1024 * 1024 * 1024, "");
DEFINE_int32(rsfs_snode_worker_thread_num, 5, "");

