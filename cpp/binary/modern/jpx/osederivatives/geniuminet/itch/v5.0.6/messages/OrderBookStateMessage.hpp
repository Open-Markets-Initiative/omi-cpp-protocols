#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/StateName.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Relays information on state changes.
struct OrderBookStateMessage {

    Nanoseconds nanoseconds;
    OrderBookId order_book_id;
    StateName state_name;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static OrderBookStateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookStateMessage*>(buffer);
    }

    // parse method const
    static const OrderBookStateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookStateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderBookStateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderBookStateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
