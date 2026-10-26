#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityShort.hpp"
#include "../types/Symbol.hpp"
#include "../types/PriceShort.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/TradeCondition.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// The Trade message provides information about executions of non-displayed orders on the Cboe book and routed executions to other trading centers. The Short variant uses a Binary Short Price and 2-byte Quantity.
struct TradeShortMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityShort quantity_short;
    Symbol symbol;
    PriceShort price_short;
    ExecutionId execution_id;
    TradeCondition trade_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x2B;

    // parse method
    static TradeShortMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeShortMessage*>(buffer);
    }

    // parse method const
    static const TradeShortMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeShortMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeShortMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeShortMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
