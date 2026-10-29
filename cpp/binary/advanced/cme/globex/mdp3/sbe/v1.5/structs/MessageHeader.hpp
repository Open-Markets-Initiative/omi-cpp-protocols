#pragma once

#include <cstddef>
#include "../types/MessageSize.hpp"
#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)

struct message_header {

    sbe_mdp3::message_size message_size;
    sbe_mdp3::simple_binary_header simple_binary_header;

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
static_assert(offsetof(message_header, message_size) == 0, "unexpected offset of message_header::message_size");
static_assert(offsetof(message_header, simple_binary_header) == 2, "unexpected offset of message_header::simple_binary_header");
static_assert(sizeof(message_header) == 10, "unexpected sizeof message_header");

#pragma pack(pop)
}
