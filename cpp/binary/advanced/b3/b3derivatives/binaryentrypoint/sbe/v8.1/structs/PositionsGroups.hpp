#pragma once

#include <cstddef>
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

struct positions_groups {

    sbe_binaryentrypoint::group_size_encoding group_size_encoding;

    // parse method
    static positions_groups* parse(std::byte* buffer) {
        return reinterpret_cast<positions_groups*>(buffer);
    }

    // parse method const
    static const positions_groups* parse(const std::byte* buffer) {
        return reinterpret_cast<const positions_groups*>(buffer);
    }
};

#pragma pack(pop)
}
