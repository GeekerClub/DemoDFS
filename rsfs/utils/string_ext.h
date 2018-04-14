// Copyright (C) 2012, for GeekerClub authors.
// Author: An Qin (anqin.qin@gmail.com)
//
// Description:


#ifndef BVS_COMMON_STRING_EXT_H
#define BVS_COMMON_STRING_EXT_H

#include <string>
#include <vector>

namespace rsfs {
namespace utils {


void SplitString(const std::string& full,
                 const std::string& delim,
                 std::vector<std::string>* result);

void SplitStringEnd(const std::string& full,
                    std::string* begin_part,
                    std::string* end_part,
                    std::string delim = ".");

std::string ReplaceString(const std::string& str,
                          const std::string& src,
                          const std::string& dest);


std::string TrimString(const std::string& str,
                       const std::string& trim = " ");

bool StringEndsWith(const std::string& str,
                    const std::string& sub_str);

bool StringStartWith(const std::string& str,
                    const std::string& sub_str);

char* StringAsArray(std::string* str);

} // namespace utils
} // namespace rsfs

#endif // BVS_COMMON_STRING_EXT_H
