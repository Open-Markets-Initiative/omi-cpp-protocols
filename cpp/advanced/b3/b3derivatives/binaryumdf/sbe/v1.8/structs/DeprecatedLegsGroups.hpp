#pragma once

#include <cstddef>
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

#pragma pack(push, 1)

struct deprecated_legs_groups {

    sbe_binaryumdf::group_size_encoding group_size_encoding;

    // parse method
    static deprecated_legs_groups* parse(std::byte* buffer) {
        return reinterpret_cast<deprecated_legs_groups*>(buffer);
    }

    // parse method const
    static const deprecated_legs_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const deprecated_legs_groups*>(buffer);
    }
};

#pragma pack(pop)
}
