#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/CanceledQuantityShort.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// Reduce Size messages are sent when a visible order on the Cboe book is partially reduced.
struct ReduceSizeShortMessage {

    TimeOffset time_offset;
    OrderId order_id;
    CanceledQuantityShort canceled_quantity_short;

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
