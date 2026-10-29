#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityBinary4.hpp"
#include "../types/PriceBinaryLongPrice8.hpp"
#include "../bitfields/ModifyFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Modify Order message (long)
struct ModifyOrderLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    QuantityBinary4 quantity_binary_4;
    PriceBinaryLongPrice8 price_binary_long_price_8;
    ModifyFlags modify_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x27;

    // parse method
    static ModifyOrderLongMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ModifyOrderLongMessage*>(buffer);
    }

    // parse method const
    static const ModifyOrderLongMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ModifyOrderLongMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ModifyOrderLongMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ModifyOrderLongMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
