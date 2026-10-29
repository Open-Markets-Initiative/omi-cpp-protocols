#pragma once

#include "../types/Timestamp.hpp"
#include "../types/OrderToken.hpp"
#include "../types/ClientReference.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/Price.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/FirmId.hpp"
#include "../types/Display.hpp"
#include "../types/Capacity.hpp"
#include "../types/OrderNumber.hpp"
#include "../types/MinimumQuantity.hpp"
#include "../types/OrderState.hpp"
#include "../types/OrderClassification.hpp"
#include "../types/CashMarginType.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// An Order Accepted Message acknowledges the receipt and acceptance of a valid Enter Order Message
struct OrderAcceptedMessage {

    Timestamp timestamp;
    OrderToken order_token;
    ClientReference client_reference;
    BuySellIndicator buy_sell_indicator;
    Quantity quantity;
    OrderbookId orderbook_id;
    Group group;
    Price price;
    TimeInForce time_in_force;
    FirmId firm_id;
    Display display;
    Capacity capacity;
    OrderNumber order_number;
    MinimumQuantity minimum_quantity;
    OrderState order_state;
    OrderClassification order_classification;
    CashMarginType cash_margin_type;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static OrderAcceptedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderAcceptedMessage*>(buffer);
    }

    // parse method const
    static const OrderAcceptedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderAcceptedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderAcceptedMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const OrderAcceptedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
