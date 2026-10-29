#pragma once

#include "../types/MessageLength.hpp"
#include "../types/MessageCategory.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct Message {

    MessageLength message_length;
    MessageCategory message_category;

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
