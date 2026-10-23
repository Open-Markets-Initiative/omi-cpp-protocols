#pragma once

#include <cstddef>
#include "../types/MessageSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)

struct message {

    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header message_header;

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
