#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/CanceledQuantity.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// An order on the book modified by a partial cancellation
struct OrderCancelMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderReferenceNumber order_reference_number;
    CanceledQuantity canceled_quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static OrderCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderCancelMessage*>(buffer);
    }

    // parse method const
    static const OrderCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderCancelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
