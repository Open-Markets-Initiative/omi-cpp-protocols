#pragma once

#include <cstddef>
#include "../types/MessageLength.hpp"
#include "../types/EncodingType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_1;

#pragma pack(push, 1)

struct framing_header {

    sbe_binaryumdf::message_length message_length;
    sbe_binaryumdf::encoding_type encoding_type;

    // parse method
    static framing_header* parse(std::byte* buffer) {
        return reinterpret_cast<framing_header*>(buffer);
    }

    // parse method const
    static const framing_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const framing_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(framing_header, message_length) == 0, "unexpected offset of framing_header::message_length");
static_assert(offsetof(framing_header, encoding_type) == 2, "unexpected offset of framing_header::encoding_type");
static_assert(sizeof(framing_header) == 4, "unexpected sizeof framing_header");

#pragma pack(pop)
}
