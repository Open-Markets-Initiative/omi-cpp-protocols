#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/Instrument.hpp"
#include "../types/OrderBookType.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Sent to instruct recipients to remove all orders from the order book for the specified instrument.
struct OrderBookClearMessage {

    Timestamp timestamp;
    SourceVenue source_venue;
    Instrument instrument;
    OrderBookType order_book_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x79;

    // parse method
    static OrderBookClearMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookClearMessage*>(buffer);
    }

    // parse method const
    static const OrderBookClearMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookClearMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderBookClearMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderBookClearMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
