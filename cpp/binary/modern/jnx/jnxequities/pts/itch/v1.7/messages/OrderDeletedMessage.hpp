#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

#pragma pack(push, 1)

// Order Deleted Message is sent whenever an order in the book has been canceled.
struct OrderDeletedMessage {

    Nanoseconds nanoseconds;
    OrderNumber order_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static OrderDeletedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeletedMessage*>(buffer);
    }

    // parse method const
    static const OrderDeletedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeletedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDeletedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderDeletedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
