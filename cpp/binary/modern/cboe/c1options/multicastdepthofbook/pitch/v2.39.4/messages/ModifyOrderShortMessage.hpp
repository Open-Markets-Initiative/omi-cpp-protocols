#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/ShortQuantity.hpp"
#include "../types/ShortPrice.hpp"
#include "../bitfields/ModifyFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message.
struct ModifyOrderShortMessage {

    TimeOffset time_offset;
    OrderId order_id;
    ShortQuantity short_quantity;
    ShortPrice short_price;
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
