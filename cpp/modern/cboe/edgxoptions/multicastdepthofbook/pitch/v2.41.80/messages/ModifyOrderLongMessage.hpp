#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityLong.hpp"
#include "../types/PriceLong.hpp"
#include "../bitfields/ModifyFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// The Modify Order message is sent whenever an open order is visibly modified. The Order Id refers to the Order Id of the original Add Order message. Note that Modify Order messages that appear to be "No Ops" (i.e. they do not appear to modify any relevant fields) will still lose priority.
struct ModifyOrderLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    QuantityLong quantity_long;
    PriceLong price_long;
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
