#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/ExecutionPrice.hpp"
#include "../types/LiquidityIndicator.hpp"
#include "../types/MatchNumber.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// An Order Executed Message denotes that all or part of an order has been executed
struct OrderExecutedMessage {

    Timestamp timestamp;
    OrderToken order_token;
    ExecutedQuantity executed_quantity;
    ExecutionPrice execution_price;
    LiquidityIndicator liquidity_indicator;
    MatchNumber match_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static OrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
