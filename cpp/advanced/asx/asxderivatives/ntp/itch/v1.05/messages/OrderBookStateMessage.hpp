#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/SessionState.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Order Book State Message
struct order_book_state_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::session_state session_state;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::order_book_state_message};

    fields_type fields;

    // parse method
    static order_book_state_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_book_state_message*>(buffer);
    }

    // parse method const
    static const order_book_state_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_book_state_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_book_state_message::fields_type, nanoseconds) == 0, "unexpected offset of order_book_state_message::fields_type::nanoseconds");
static_assert(offsetof(order_book_state_message::fields_type, trade_date) == 4, "unexpected offset of order_book_state_message::fields_type::trade_date");
static_assert(offsetof(order_book_state_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of order_book_state_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(order_book_state_message::fields_type, session_state) == 10, "unexpected offset of order_book_state_message::fields_type::session_state");
static_assert(sizeof(order_book_state_message::fields_type) == 11, "unexpected sizeof order_book_state_message::fields_type");
static_assert(sizeof(order_book_state_message) == sizeof(itch_ntp::message_header) + 11, "unexpected sizeof order_book_state_message");

#pragma pack(pop)
}
