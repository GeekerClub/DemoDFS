// Copyright (C) 2016, For toft authors.
// Author: Pengyu Sun (sunpengyu@nbjl.nankai.edu.cn)
//
// Description:

//#include <stdint>

#include "toft/container/counter.h"

// ***** io *****
DEFINE_COUNTER(Rate, rsfs_io_size_counter, "data size of io");
DEFINE_COUNTER(Rate, rsfs_io_times_counter, "data access times of io");
DEFINE_COUNTER(Rate, rsfs_query_counter, "query per second");
