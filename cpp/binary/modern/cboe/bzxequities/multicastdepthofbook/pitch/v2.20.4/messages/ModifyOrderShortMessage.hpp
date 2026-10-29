#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityBinary2.hpp"
#include "../types/PriceBinaryShortPrice2.hpp"
#include "../bitfields/ModifyFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Modify Order message (short)
struct ModifyOrderShortMessage {

    TimeOffset time_offset;
    OrderId order_id;
    QuantityBinary2 quantity_binary_2;
    PriceBinaryShortPrice2 price_binary_short_price_2;
    ModifyFlags modify_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x28;

    // parse method
    static ModifyOrderShortMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ModifyOrderShortMessage*>(buffer);
    }

    // parse method const
    static const ModifyOrderShortMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ModifyOrderShortMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ModifyOrderShortMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ModifyOrderShortMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
