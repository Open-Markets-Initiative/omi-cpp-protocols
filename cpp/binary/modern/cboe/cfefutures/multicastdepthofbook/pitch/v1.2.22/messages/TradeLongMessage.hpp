#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityLong.hpp"
#include "../types/Symbol.hpp"
#include "../types/PriceLong.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/TradeCondition.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Trade message provides information about executions that occur off of the CFE book (such as ECRP/Block trades). Trade messages are necessary to calculate CFE execution data.
struct TradeLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityLong quantity_long;
    Symbol symbol;
    PriceLong price_long;
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
