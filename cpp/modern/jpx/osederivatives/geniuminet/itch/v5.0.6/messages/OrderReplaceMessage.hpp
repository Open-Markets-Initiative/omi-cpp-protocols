#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Side.hpp"
#include "../types/NewOrderbookPosition.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../bitfields/OrderAttributes.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Sent whenever an existing order on the book has been modified. Note: Specification says this message is not used, but remains for future reference.
struct OrderReplaceMessage {

    Nanoseconds nanoseconds;
    OrderId order_id;
    OrderBookId order_book_id;
    Side side;
    NewOrderbookPosition new_orderbook_position;
    Quantity quantity;
    Price price;
    OrderAttributes order_attributes;

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
