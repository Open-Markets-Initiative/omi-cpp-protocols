#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/DecrementQuantity.hpp"
#include "../types/OrderCanceledReason.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// An Order Canceled Message denotes that an order has been canceled
struct OrderCanceledMessage {

    Timestamp timestamp;
    OrderToken order_token;
    DecrementQuantity decrement_quantity;
    OrderCanceledReason order_canceled_reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'C';

    // parse method
    static OrderCanceledMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderCanceledMessage*>(buffer);
    }

    // parse method const
    static const OrderCanceledMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderCanceledMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderCanceledMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OrderCanceledMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
