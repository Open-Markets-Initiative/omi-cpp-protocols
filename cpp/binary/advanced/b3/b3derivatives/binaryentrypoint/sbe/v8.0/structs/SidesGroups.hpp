#pragma once

#include <cstddef>
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

struct sides_groups {

    sbe_binaryentrypoint::group_size_encoding group_size_encoding;

    // parse method
    static sides_groups* parse(std::byte* buffer) {
        return reinterpret_cast<sides_groups*>(buffer);
    }

    // parse method const
    static const sides_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const sides_groups*>(buffer);
    }
};

#pragma pack(pop)
}
