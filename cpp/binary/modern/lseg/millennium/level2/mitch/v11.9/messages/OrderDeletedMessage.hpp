#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../bitfields/OrderDeletedFlags.hpp"
#include "../types/InstrumentId.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Sent to indicate that the remainder of a displayed order is cancelled.
struct OrderDeletedMessage {

    Nanosecond nanosecond;
    OrderId order_id;
    OrderDeletedFlags order_deleted_flags;
    InstrumentId instrument_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x44;

    // parse method
    static OrderDeletedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeletedMessage*>(buffer);
    }

    // parse method const
    static const OrderDeletedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeletedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDeletedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderDeletedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
