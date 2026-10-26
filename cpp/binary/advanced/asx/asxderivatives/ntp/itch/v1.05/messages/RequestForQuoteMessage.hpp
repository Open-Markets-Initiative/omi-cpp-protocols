#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/RfqSide.hpp"
#include "../types/Quantity.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Request For Quote Message
struct request_for_quote_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::rfq_side rfq_side;
        itch_ntp::quantity quantity;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::request_for_quote_message};

    fields_type fields;

    // parse method
    static request_for_quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<request_for_quote_message*>(buffer);
    }

    // parse method const
    static const request_for_quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const request_for_quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(request_for_quote_message::fields_type, nanoseconds) == 0, "unexpected offset of request_for_quote_message::fields_type::nanoseconds");
static_assert(offsetof(request_for_quote_message::fields_type, trade_date) == 4, "unexpected offset of request_for_quote_message::fields_type::trade_date");
static_assert(offsetof(request_for_quote_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of request_for_quote_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(request_for_quote_message::fields_type, rfq_side) == 10, "unexpected offset of request_for_quote_message::fields_type::rfq_side");
static_assert(offsetof(request_for_quote_message::fields_type, quantity) == 11, "unexpected offset of request_for_quote_message::fields_type::quantity");
static_assert(sizeof(request_for_quote_message::fields_type) == 15, "unexpected sizeof request_for_quote_message::fields_type");
static_assert(sizeof(request_for_quote_message) == sizeof(itch_ntp::message_header) + 15, "unexpected sizeof request_for_quote_message");

#pragma pack(pop)
}
