#pragma once

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
#include "../types/MinimumQuantity.hpp"
#include "../types/OrderClassification.hpp"
#include "../types/CashMarginType.hpp"
#include "../messages/UnsequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// An Enter Order Message is used to enter a new order into the Japannext PTS execution system
struct EnterOrderMessage {

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
    MinimumQuantity minimum_quantity;
    OrderClassification order_classification;
    CashMarginType cash_margin_type;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static EnterOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EnterOrderMessage*>(buffer);
    }

    // parse method const
    static const EnterOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EnterOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EnterOrderMessage* parse(const UnsequencedDataPacket* header) {
        return reinterpret_cast<const EnterOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(UnsequencedDataPacket));
    }
};

#pragma pack(pop)
}
