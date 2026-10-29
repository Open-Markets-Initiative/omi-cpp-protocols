#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OriginalOrderNumber.hpp"
#include "../types/NewOrderNumber.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

#pragma pack(push, 1)

// Order Replaced Message is sent whenever an order in the book has been replaced.
struct OrderReplacedMessage {

    Nanoseconds nanoseconds;
    OriginalOrderNumber original_order_number;
    NewOrderNumber new_order_number;
    Quantity quantity;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'U';

    // parse method
    static OrderReplacedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderReplacedMessage*>(buffer);
    }

    // parse method const
    static const OrderReplacedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderReplacedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderReplacedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderReplacedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
