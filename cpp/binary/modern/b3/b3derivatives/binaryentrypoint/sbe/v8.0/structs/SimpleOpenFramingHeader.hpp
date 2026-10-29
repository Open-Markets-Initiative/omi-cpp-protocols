#pragma once

#include "../types/MessageLength.hpp"
#include "../types/EncodingType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

struct SimpleOpenFramingHeader {

    MessageLength message_length;
    EncodingType encoding_type;

    // parse method
    static SimpleOpenFramingHeader* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleOpenFramingHeader*>(buffer);
    }

    // parse method const
    static const SimpleOpenFramingHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleOpenFramingHeader*>(buffer);
    }
};

#pragma pack(pop)
}
