#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/TradingState.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

#pragma pack(push, 1)

// Trading State Message indicates the current trading state of an orderbook.
struct TradingStateMessage {

    Nanoseconds nanoseconds;
    OrderbookId orderbook_id;
    Group group;
    TradingState trading_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static TradingStateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingStateMessage*>(buffer);
    }

    // parse method const
    static const TradingStateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingStateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradingStateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradingStateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
