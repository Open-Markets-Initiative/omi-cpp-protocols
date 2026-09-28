#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../structs/MessageHeader.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

#pragma pack(push, 1)

struct message {

    sbe_binaryumdf::framing_header framing_header;
    sbe_binaryumdf::message_header message_header;

    // parse method
    static message* parse(std::byte* buffer) {
        return reinterpret_cast<message*>(buffer);
    }

    // parse method const
    static const message* parse(const std::byte* buffer) {
        return reinterpret_cast<const message*>(buffer);
    }
};

#pragma pack(pop)
}
