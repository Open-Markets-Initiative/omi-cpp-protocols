#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/DecrementQuantity.hpp"
#include "../types/OrderCanceledReason.hpp"
#include "../types/QuantityPreventedFromTrading.hpp"
#include "../types/ExecutionPrice.hpp"
#include "../types/LiquidityIndicator.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// An Order AIQ Canceled Message denotes that an order has been canceled by Japannext PTS to prevent a self-trade
struct OrderAiqCanceledMessage {

    Timestamp timestamp;
    OrderToken order_token;
    DecrementQuantity decrement_quantity;
    OrderCanceledReason order_canceled_reason;
    QuantityPreventedFromTrading quantity_prevented_from_trading;
    ExecutionPrice execution_price;
    LiquidityIndicator liquidity_indicator;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static OrderAiqCanceledMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderAiqCanceledMessage*>(buffer);
    }

    // parse method const
    static const OrderAiqCanceledMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderAiqCanceledMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderAiqCanceledMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OrderAiqCanceledMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
