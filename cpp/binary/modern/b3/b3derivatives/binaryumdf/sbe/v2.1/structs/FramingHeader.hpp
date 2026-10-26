#pragma once

#include "../types/MessageLength.hpp"
#include "../types/EncodingType.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

#pragma pack(push, 1)

struct FramingHeader {

    MessageLength message_length;
    EncodingType encoding_type;

    // parse method
    static FramingHeader* parse(std::byte* buffer) {
        return reinterpret_cast<FramingHeader*>(buffer);
    }

    // parse method const
    static const FramingHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const FramingHeader*>(buffer);
    }
};

#pragma pack(pop)
}
