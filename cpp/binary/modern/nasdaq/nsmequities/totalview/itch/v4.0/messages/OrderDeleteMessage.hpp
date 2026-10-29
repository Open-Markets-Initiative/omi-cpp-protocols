#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// This message is sent whenever an order on the book is being cancelled. All remaining shares are no longer accessible so the order must be removed from the book.
struct OrderDeleteMessage {

    Nanoseconds nanoseconds;
    OrderReferenceNumber order_reference_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static OrderDeleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeleteMessage*>(buffer);
    }

    // parse method const
    static const OrderDeleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeleteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDeleteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderDeleteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
