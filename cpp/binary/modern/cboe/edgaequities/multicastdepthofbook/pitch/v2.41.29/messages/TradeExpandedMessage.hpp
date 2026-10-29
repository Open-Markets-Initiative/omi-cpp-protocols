#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/Price.hpp"
#include "../types/ExecutionId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// The Trade message provides information about executions of complex order auctions on the Cboe complex book.
struct TradeExpandedMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    Quantity quantity;
    SymbolLong symbol_long;
    Price price;
    ExecutionId execution_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x30;

    // parse method
    static TradeExpandedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeExpandedMessage*>(buffer);
    }

    // parse method const
    static const TradeExpandedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeExpandedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeExpandedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeExpandedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
