#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OriginalOrderReferenceNumber.hpp"
#include "../types/NewOrderReferenceNumber.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// An order on the book has been cancel replaced
struct OrderReplaceMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OriginalOrderReferenceNumber original_order_reference_number;
    NewOrderReferenceNumber new_order_reference_number;
    Quantity quantity;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'U';

    // parse method
    static OrderReplaceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderReplaceMessage*>(buffer);
    }

    // parse method const
    static const OrderReplaceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderReplaceMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderReplaceMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderReplaceMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
