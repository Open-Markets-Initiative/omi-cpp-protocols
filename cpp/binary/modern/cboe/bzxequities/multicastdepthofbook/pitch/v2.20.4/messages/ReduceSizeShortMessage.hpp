#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/CanceledQuantityBinary2.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Reduce Size message (short)
struct ReduceSizeShortMessage {

    TimeOffset time_offset;
    OrderId order_id;
    CanceledQuantityBinary2 canceled_quantity_binary_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x26;

    // parse method
    static ReduceSizeShortMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ReduceSizeShortMessage*>(buffer);
    }

    // parse method const
    static const ReduceSizeShortMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ReduceSizeShortMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ReduceSizeShortMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ReduceSizeShortMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
