#pragma once

#include <cstddef>
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_1;

#pragma pack(push, 1)

struct legs_groups {

    sbe_binaryumdf::group_size_encoding group_size_encoding;

    // parse method
    static legs_groups* parse(std::byte* buffer) {
        return reinterpret_cast<legs_groups*>(buffer);
    }

    // parse method const
    static const legs_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const legs_groups*>(buffer);
    }
};

#pragma pack(pop)
}
