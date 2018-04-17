// Copyright (C) 2018, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:

#ifndef RSFS_TYPES_H
#define RSFS_TYPES_H

#include <stdint.h>

#include "thirdparty/glog/logging.h"
#include "thirdparty/gflags/gflags.h"


namespace rsfs {

typedef int32_t TabletNodeId;

const int32_t kInvalidId = -1;
const uint64_t kSequenceIDStart = 0;
const uint64_t kInvalidTimerId = 0;
const uint32_t kUnknownId = -1U;
const uint32_t kInvalidSessionId = -1U;
const std::string kUnknownAddr = "255.255.255.255:0000";
const uint64_t kMaxTimeStamp = (1ULL << 56) - 1;
const uint32_t kMaxLevel = UINT32_MAX;

} // namespace rsfs

#endif // RSFS_TYPES_H
