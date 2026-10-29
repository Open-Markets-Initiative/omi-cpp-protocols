#pragma once

#include "../types/Timestamp.hpp"
#include "../types/ReplacementOrderToken.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/Price.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/Display.hpp"
#include "../types/OrderNumber.hpp"
#include "../types/MinimumQuantity.hpp"
#include "../types/OrderState.hpp"
#include "../types/PreviousOrderToken.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// An Order Replaced Message acknowledges the receipt and acceptance of a valid Replace Order Message
struct OrderReplacedMessage {

    Timestamp timestamp;
    ReplacementOrderToken replacement_order_token;
    BuySellIndicator buy_sell_indicator;
    Quantity quantity;
    OrderbookId orderbook_id;
    Group group;
    Price price;
    TimeInForce time_in_force;
    Display display;
    OrderNumber order_number;
    MinimumQuantity minimum_quantity;
    OrderState order_state;
    PreviousOrderToken previous_order_token;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'U';

    // parse method
    static OrderReplacedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderReplacedMessage*>(buffer);
    }

    // parse method const
    static const OrderReplacedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderReplacedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderReplacedMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OrderReplacedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
