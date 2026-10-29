#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityBinary4.hpp"
#include "../types/SymbolShort.hpp"
#include "../types/PriceBinaryLongPrice8.hpp"
#include "../bitfields/AddFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Add Order message (long)
struct AddOrderLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityBinary4 quantity_binary_4;
    SymbolShort symbol_short;
    PriceBinaryLongPrice8 price_binary_long_price_8;
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
