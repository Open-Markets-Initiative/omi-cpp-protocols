#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/TradeId.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Trade Cancellation Message
struct trade_cancellation_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::trade_id trade_id;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_cancellation_message};

    fields_type fields;

    // parse method
    static trade_cancellation_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_cancellation_message*>(buffer);
    }

    // parse method const
    static const trade_cancellation_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_cancellation_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_cancellation_message::fields_type, nanoseconds) == 0, "unexpected offset of trade_cancellation_message::fields_type::nanoseconds");
static_assert(offsetof(trade_cancellation_message::fields_type, trade_date) == 4, "unexpected offset of trade_cancellation_message::fields_type::trade_date");
static_assert(offsetof(trade_cancellation_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of trade_cancellation_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(trade_cancellation_message::fields_type, trade_id) == 10, "unexpected offset of trade_cancellation_message::fields_type::trade_id");
static_assert(sizeof(trade_cancellation_message::fields_type) == 18, "unexpected sizeof trade_cancellation_message::fields_type");
static_assert(sizeof(trade_cancellation_message) == sizeof(itch_ntp::message_header) + 18, "unexpected sizeof trade_cancellation_message");

#pragma pack(pop)
}
