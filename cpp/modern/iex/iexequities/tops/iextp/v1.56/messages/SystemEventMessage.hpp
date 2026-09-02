#pragma once

#include "../types/SystemEvent.hpp"
#include "../types/Timestamp.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

#pragma pack(push, 1)

// The System Event Message is used to indicate events that apply to the market or the data feed.
struct SystemEventMessage {

    SystemEvent system_event;
    Timestamp timestamp;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'S';

    // parse method
    static SystemEventMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SystemEventMessage*>(buffer);
    }

    // parse method const
    static const SystemEventMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SystemEventMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SystemEventMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SystemEventMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
