#pragma once

#include "../types/Reserved2.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Event.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Transitions in the overall session state
struct MarketEventMessage {

    Reserved2 reserved_2;
    Timestamp timestamp;
    Event event;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static MarketEventMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MarketEventMessage*>(buffer);
    }

    // parse method const
    static const MarketEventMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MarketEventMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MarketEventMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MarketEventMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
