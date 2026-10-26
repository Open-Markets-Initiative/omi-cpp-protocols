#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityRemaining.hpp"
#include "../types/TradeType.hpp"
#include "../types/TradeId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/TradePrice.hpp"
#include "../types/CombinationTradeId.hpp"
#include "../types/CounterPartyId.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Order Executed Message
struct order_executed_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::side side;
        itch_ntp::order_id order_id;
        itch_ntp::quantity_remaining quantity_remaining;
        itch_ntp::trade_type trade_type;
        itch_ntp::trade_id trade_id;
        itch_ntp::executed_quantity executed_quantity;
        itch_ntp::trade_price trade_price;
        itch_ntp::combination_trade_id combination_trade_id;
        itch_ntp::counter_party_id counter_party_id;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_executed_message};

    fields_type fields;

    // parse method
    static order_executed_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_executed_message*>(buffer);
    }

    // parse method const
    static const order_executed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_executed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_executed_message::fields_type, nanoseconds) == 0, "unexpected offset of order_executed_message::fields_type::nanoseconds");
static_assert(offsetof(order_executed_message::fields_type, trade_date) == 4, "unexpected offset of order_executed_message::fields_type::trade_date");
static_assert(offsetof(order_executed_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of order_executed_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(order_executed_message::fields_type, side) == 10, "unexpected offset of order_executed_message::fields_type::side");
static_assert(offsetof(order_executed_message::fields_type, order_id) == 11, "unexpected offset of order_executed_message::fields_type::order_id");
static_assert(offsetof(order_executed_message::fields_type, quantity_remaining) == 19, "unexpected offset of order_executed_message::fields_type::quantity_remaining");
static_assert(offsetof(order_executed_message::fields_type, trade_type) == 23, "unexpected offset of order_executed_message::fields_type::trade_type");
static_assert(offsetof(order_executed_message::fields_type, trade_id) == 24, "unexpected offset of order_executed_message::fields_type::trade_id");
static_assert(offsetof(order_executed_message::fields_type, executed_quantity) == 32, "unexpected offset of order_executed_message::fields_type::executed_quantity");
static_assert(offsetof(order_executed_message::fields_type, trade_price) == 36, "unexpected offset of order_executed_message::fields_type::trade_price");
static_assert(offsetof(order_executed_message::fields_type, combination_trade_id) == 44, "unexpected offset of order_executed_message::fields_type::combination_trade_id");
static_assert(offsetof(order_executed_message::fields_type, counter_party_id) == 52, "unexpected offset of order_executed_message::fields_type::counter_party_id");
static_assert(sizeof(order_executed_message::fields_type) == 55, "unexpected sizeof order_executed_message::fields_type");
static_assert(sizeof(order_executed_message) == sizeof(itch_ntp::message_header) + 55, "unexpected sizeof order_executed_message");

#pragma pack(pop)
}
