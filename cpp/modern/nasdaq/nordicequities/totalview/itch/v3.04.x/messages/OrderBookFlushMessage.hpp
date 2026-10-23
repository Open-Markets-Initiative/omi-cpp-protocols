#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderBook.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// An order book is flushed and all orders removed
struct OrderBookFlushMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderBook order_book;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Y';

    // parse method
    static OrderBookFlushMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookFlushMessage*>(buffer);
    }

    // parse method const
    static const OrderBookFlushMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookFlushMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderBookFlushMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderBookFlushMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
