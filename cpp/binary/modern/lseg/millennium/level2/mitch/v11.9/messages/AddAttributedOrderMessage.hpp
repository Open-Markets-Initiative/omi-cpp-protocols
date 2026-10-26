#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../types/Attribution.hpp"
#include "../bitfields/AddAttributedOrderFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Indicates that a named order is added to the order book.
struct AddAttributedOrderMessage {

    Nanosecond nanosecond;
    OrderId order_id;
    Side side;
    Quantity quantity;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    Price price;
    Attribution attribution;
    AddAttributedOrderFlags add_attributed_order_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x46;

    // parse method
    static AddAttributedOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddAttributedOrderMessage*>(buffer);
    }

    // parse method const
    static const AddAttributedOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddAttributedOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddAttributedOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddAttributedOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
