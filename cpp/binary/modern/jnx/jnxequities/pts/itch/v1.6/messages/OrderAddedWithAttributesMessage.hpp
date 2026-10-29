#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderNumber.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/Price.hpp"
#include "../types/Attribution.hpp"
#include "../types/OrderType.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

#pragma pack(push, 1)

// Order Added with Attributes Message will be generated for orders with market specific attributes accepted by the system.
struct OrderAddedWithAttributesMessage {

    Nanoseconds nanoseconds;
    OrderNumber order_number;
    BuySellIndicator buy_sell_indicator;
    Quantity quantity;
    OrderbookId orderbook_id;
    Group group;
    Price price;
    Attribution attribution;
    OrderType order_type;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'F';

    // parse method
    static OrderAddedWithAttributesMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderAddedWithAttributesMessage*>(buffer);
    }

    // parse method const
    static const OrderAddedWithAttributesMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderAddedWithAttributesMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderAddedWithAttributesMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderAddedWithAttributesMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
