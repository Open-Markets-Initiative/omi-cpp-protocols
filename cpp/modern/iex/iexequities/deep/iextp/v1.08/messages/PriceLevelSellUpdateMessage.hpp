#pragma once

#include "../types/EventFlags.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Symbol.hpp"
#include "../types/Size.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

#pragma pack(push, 1)

// Deep broadcasts a real-time Price Level Update Message each time a displayed price level on IEX is updated during the trading day
struct PriceLevelSellUpdateMessage {

    EventFlags event_flags;
    Timestamp timestamp;
    Symbol symbol;
    Size size;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = '5';

    // parse method
    static PriceLevelSellUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriceLevelSellUpdateMessage*>(buffer);
    }

    // parse method const
    static const PriceLevelSellUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriceLevelSellUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const PriceLevelSellUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const PriceLevelSellUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
