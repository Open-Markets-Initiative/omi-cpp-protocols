#pragma once

#include "../types/MessageLength.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

struct Message {

    MessageLength message_length;

    // parse method
    static Message* parse(std::byte* buffer) {
        return reinterpret_cast<Message*>(buffer);
    }

    // parse method const
    static const Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const Message*>(buffer);
    }
};

#pragma pack(pop)
}
