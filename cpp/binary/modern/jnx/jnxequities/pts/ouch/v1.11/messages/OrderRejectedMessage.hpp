#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/OrderRejectedReason.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// An Order Rejected Message may be sent in response to an Enter Order Message if the order cannot be accepted
struct OrderRejectedMessage {

    Timestamp timestamp;
    OrderToken order_token;
    OrderRejectedReason order_rejected_reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static OrderRejectedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderRejectedMessage*>(buffer);
    }

    // parse method const
    static const OrderRejectedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderRejectedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderRejectedMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OrderRejectedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
