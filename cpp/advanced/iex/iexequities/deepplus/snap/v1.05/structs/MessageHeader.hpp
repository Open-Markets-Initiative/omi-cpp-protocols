#pragma once

#include <cstddef>
#include "../types/MessageLength.hpp"
#include "../types/MessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

namespace snap_deepplus = ::iex::iexequities::deepplus::snap::v1_05;

#pragma pack(push, 1)

struct message_header {

    snap_deepplus::message_length message_length;
    snap_deepplus::message_type message_type;

    // parse method
    static message_header* parse(std::byte* buffer) {
        return reinterpret_cast<message_header*>(buffer);
    }

    // parse method const
    static const message_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(message_header, message_length) == 0, "unexpected offset of message_header::message_length");
static_assert(offsetof(message_header, message_type) == 2, "unexpected offset of message_header::message_type");
static_assert(sizeof(message_header) == 3, "unexpected sizeof message_header");

#pragma pack(pop)
}
