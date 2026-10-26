#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../bitfields/OrderBookClearFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Sent to instruct recipients to remove all orders from the order book for the specified instrument.
struct OrderBookClearMessage {

    Nanosecond nanosecond;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    OrderBookClearFlags order_book_clear_flags;

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
