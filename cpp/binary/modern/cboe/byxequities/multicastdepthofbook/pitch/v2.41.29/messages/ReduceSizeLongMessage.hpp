#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/CanceledQuantity.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// Reduce Size messages are sent when a visible order on the Cboe book is partially reduced.
struct ReduceSizeLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    CanceledQuantity canceled_quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x25;

    // parse method
    static ReduceSizeLongMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ReduceSizeLongMessage*>(buffer);
    }

    // parse method const
    static const ReduceSizeLongMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ReduceSizeLongMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ReduceSizeLongMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ReduceSizeLongMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
