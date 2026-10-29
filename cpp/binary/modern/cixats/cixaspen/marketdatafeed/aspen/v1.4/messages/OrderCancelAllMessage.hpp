#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Sent when the order is canceled in its entirety
struct OrderCancelAllMessage {

    Timestamp timestamp;
    OrderId order_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'G';

    // parse method
    static OrderCancelAllMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderCancelAllMessage*>(buffer);
    }

    // parse method const
    static const OrderCancelAllMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderCancelAllMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderCancelAllMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderCancelAllMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
