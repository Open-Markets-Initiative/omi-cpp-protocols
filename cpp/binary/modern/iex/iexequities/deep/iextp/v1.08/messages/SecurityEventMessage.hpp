#pragma once

#include "../types/SecurityEvent.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

#pragma pack(push, 1)

// The Security Event Message is used to indicate events that apply to a security
struct SecurityEventMessage {

    SecurityEvent security_event;
    Timestamp timestamp;
    Symbol symbol;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static SecurityEventMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityEventMessage*>(buffer);
    }

    // parse method const
    static const SecurityEventMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityEventMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityEventMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecurityEventMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
