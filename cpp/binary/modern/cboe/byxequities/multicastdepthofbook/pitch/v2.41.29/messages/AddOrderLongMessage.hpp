#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/SymbolShort.hpp"
#include "../types/Price.hpp"
#include "../bitfields/AddOrderFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// An Add Order message represents a newly accepted visible order on the Cboe book
struct AddOrderLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    Quantity quantity;
    SymbolShort symbol_short;
    Price price;
    AddOrderFlags add_order_flags;

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
