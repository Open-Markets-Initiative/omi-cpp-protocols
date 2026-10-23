#pragma once

#include "../structs/MessageHeader.hpp"

namespace cme::mdp3::v8 {

#pragma pack(push, 1)

// SubscriberHeartbeat
struct SubscriberHeartbeat {


    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 210;

    // parse method
    static SubscriberHeartbeat* parse(std::byte* buffer) {
        return reinterpret_cast<SubscriberHeartbeat*>(buffer);
    }

    // parse method const
    static const SubscriberHeartbeat* parse(const std::byte* buffer) {
        return reinterpret_cast<const SubscriberHeartbeat*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SubscriberHeartbeat* parse(const MessageHeader* header) {
        return reinterpret_cast<const SubscriberHeartbeat*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
