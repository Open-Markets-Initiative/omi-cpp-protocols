#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Order Deleted Message
struct order_deleted_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::side side;
        itch_ntp::order_id order_id;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_deleted_message};

    fields_type fields;

    // parse method
    static order_deleted_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_deleted_message*>(buffer);
    }

    // parse method const
    static const order_deleted_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_deleted_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_deleted_message::fields_type, nanoseconds) == 0, "unexpected offset of order_deleted_message::fields_type::nanoseconds");
static_assert(offsetof(order_deleted_message::fields_type, trade_date) == 4, "unexpected offset of order_deleted_message::fields_type::trade_date");
static_assert(offsetof(order_deleted_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of order_deleted_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(order_deleted_message::fields_type, side) == 10, "unexpected offset of order_deleted_message::fields_type::side");
static_assert(offsetof(order_deleted_message::fields_type, order_id) == 11, "unexpected offset of order_deleted_message::fields_type::order_id");
static_assert(sizeof(order_deleted_message::fields_type) == 19, "unexpected sizeof order_deleted_message::fields_type");
static_assert(sizeof(order_deleted_message) == sizeof(itch_ntp::message_header) + 19, "unexpected sizeof order_deleted_message");

#pragma pack(pop)
}
