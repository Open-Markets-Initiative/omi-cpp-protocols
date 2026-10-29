#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderNumber.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

#pragma pack(push, 1)

// Order Executed Message is sent whenever an order in the book is executed in whole or part.
struct OrderExecutedMessage {

    Nanoseconds nanoseconds;
    OrderNumber order_number;
    ExecutedQuantity executed_quantity;
    MatchNumber match_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static OrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
