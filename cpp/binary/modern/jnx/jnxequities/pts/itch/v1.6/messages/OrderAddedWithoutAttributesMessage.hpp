#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

#pragma pack(push, 1)

// Order Added Message will be generated for normal orders accepted by the system.
struct OrderAddedWithoutAttributesMessage {

    Nanoseconds nanoseconds;
    OrderNumber order_number;
    BuySellIndicator buy_sell_indicator;
    Quantity quantity;
    OrderbookId orderbook_id;
    Group group;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static OrderAddedWithoutAttributesMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderAddedWithoutAttributesMessage*>(buffer);
    }

    // parse method const
    static const OrderAddedWithoutAttributesMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderAddedWithoutAttributesMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderAddedWithoutAttributesMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderAddedWithoutAttributesMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
