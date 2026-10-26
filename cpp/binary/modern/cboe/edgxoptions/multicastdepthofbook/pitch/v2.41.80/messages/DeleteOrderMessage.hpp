#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// The Delete Order message is sent whenever a booked order is cancelled or leaves the order book. The Order Id refers to the Order Id of the original Add Order message. An order that is deleted from the book may return to the book later under certain circumstances. Therefore, a Delete Order message does not indicate that a given Order Id will not be sent again on a subsequent Add Order message.
struct DeleteOrderMessage {

    TimeOffset time_offset;
    OrderId order_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x29;

    // parse method
    static DeleteOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<DeleteOrderMessage*>(buffer);
    }

    // parse method const
    static const DeleteOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeleteOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const DeleteOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const DeleteOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
