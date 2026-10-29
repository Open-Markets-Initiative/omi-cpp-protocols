#pragma once

#include <cstddef>
#include "../types/Prefix.hpp"
#include "../types/Offset2Padding2.hpp"
#include "../types/Document.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

struct investor_id {

    sbe_binaryentrypoint::prefix prefix;
    sbe_binaryentrypoint::offset_2_padding_2 offset_2_padding_2;
    sbe_binaryentrypoint::document document;

    // parse method
    static investor_id* parse(std::byte* buffer) {
        return reinterpret_cast<investor_id*>(buffer);
    }

    // parse method const
    static const investor_id* parse(const std::byte* buffer) {
        return reinterpret_cast<const investor_id*>(buffer);
    }
};

// layout verification
static_assert(offsetof(investor_id, prefix) == 0, "unexpected offset of investor_id::prefix");
static_assert(offsetof(investor_id, offset_2_padding_2) == 2, "unexpected offset of investor_id::offset_2_padding_2");
static_assert(offsetof(investor_id, document) == 4, "unexpected offset of investor_id::document");
static_assert(sizeof(investor_id) == 8, "unexpected sizeof investor_id");

#pragma pack(pop)
}
