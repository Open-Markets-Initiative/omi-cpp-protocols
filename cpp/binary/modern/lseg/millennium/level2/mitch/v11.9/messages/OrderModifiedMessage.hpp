#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/NewQuantity.hpp"
#include "../types/NewPrice.hpp"
#include "../bitfields/OrderModifiedFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Indicates that the displayed quantity or price of a displayed order has been updated.
struct OrderModifiedMessage {

    Nanosecond nanosecond;
    OrderId order_id;
    NewQuantity new_quantity;
    NewPrice new_price;
    OrderModifiedFlags order_modified_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x55;

    // parse method
    static OrderModifiedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderModifiedMessage*>(buffer);
    }

    // parse method const
    static const OrderModifiedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderModifiedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderModifiedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderModifiedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
