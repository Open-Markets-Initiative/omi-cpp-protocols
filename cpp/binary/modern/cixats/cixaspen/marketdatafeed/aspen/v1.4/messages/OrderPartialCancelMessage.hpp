#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityCanceled.hpp"
#include "../structs/MessageHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

#pragma pack(push, 1)

// Part of a resting order is canceled
struct OrderPartialCancelMessage {

    Timestamp timestamp;
    OrderId order_id;
    QuantityCanceled quantity_canceled;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'F';

    // parse method
    static OrderPartialCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderPartialCancelMessage*>(buffer);
    }

    // parse method const
    static const OrderPartialCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderPartialCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderPartialCancelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderPartialCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
