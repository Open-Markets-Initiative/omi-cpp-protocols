#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../bitfields/AddOrderFlags.hpp"
#include "../types/Reserved10.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Sent to indicate that an anonymous limit or market order is added to the order book.
struct AddOrderMessage {

    Nanosecond nanosecond;
    OrderId order_id;
    Side side;
    Quantity quantity;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    Price price;
    AddOrderFlags add_order_flags;
    Reserved10 reserved_10;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x41;

    // parse method
    static AddOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
