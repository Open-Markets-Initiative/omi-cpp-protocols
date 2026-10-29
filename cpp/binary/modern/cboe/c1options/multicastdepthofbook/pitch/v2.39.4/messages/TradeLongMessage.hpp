#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/LongQuantity.hpp"
#include "../types/Symbol.hpp"
#include "../types/LongPrice.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/TradeCondition.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers.
struct TradeLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    LongQuantity long_quantity;
    Symbol symbol;
    LongPrice long_price;
    ExecutionId execution_id;
    TradeCondition trade_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x2A;

    // parse method
    static TradeLongMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeLongMessage*>(buffer);
    }

    // parse method const
    static const TradeLongMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeLongMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeLongMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeLongMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
