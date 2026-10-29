#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/LongQuantity.hpp"
#include "../types/Symbol.hpp"
#include "../types/LongPrice.hpp"
#include "../bitfields/AddFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// An Add Order message represents a newly accepted visible order on the Cboe book.
struct AddOrderLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    LongQuantity long_quantity;
    Symbol symbol;
    LongPrice long_price;
    AddFlags add_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x21;

    // parse method
    static AddOrderLongMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderLongMessage*>(buffer);
    }

    // parse method const
    static const AddOrderLongMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderLongMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderLongMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderLongMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
