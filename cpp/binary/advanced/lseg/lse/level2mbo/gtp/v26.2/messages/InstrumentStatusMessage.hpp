#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Instrument.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/SessionChangeReason.hpp"
#include "../types/NewEndTime.hpp"
#include "../types/OrderBookType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// Instrument Status Message
struct instrument_status_message {

    struct fields_type {
        gtp_level2mbo::timestamp timestamp;
        gtp_level2mbo::instrument instrument;
        gtp_level2mbo::source_venue source_venue;
        gtp_level2mbo::trading_status trading_status;
        gtp_level2mbo::session_change_reason session_change_reason;
        gtp_level2mbo::new_end_time new_end_time;
        gtp_level2mbo::order_book_type order_book_type;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::instrument_status_message};

    fields_type fields;

    // parse method
    static instrument_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_status_message*>(buffer);
    }

    // parse method const
    static const instrument_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_status_message::fields_type, timestamp) == 0, "unexpected offset of instrument_status_message::fields_type::timestamp");
static_assert(offsetof(instrument_status_message::fields_type, instrument) == 8, "unexpected offset of instrument_status_message::fields_type::instrument");
static_assert(offsetof(instrument_status_message::fields_type, source_venue) == 16, "unexpected offset of instrument_status_message::fields_type::source_venue");
static_assert(offsetof(instrument_status_message::fields_type, trading_status) == 18, "unexpected offset of instrument_status_message::fields_type::trading_status");
static_assert(offsetof(instrument_status_message::fields_type, session_change_reason) == 19, "unexpected offset of instrument_status_message::fields_type::session_change_reason");
static_assert(offsetof(instrument_status_message::fields_type, new_end_time) == 20, "unexpected offset of instrument_status_message::fields_type::new_end_time");
static_assert(offsetof(instrument_status_message::fields_type, order_book_type) == 26, "unexpected offset of instrument_status_message::fields_type::order_book_type");
static_assert(sizeof(instrument_status_message::fields_type) == 27, "unexpected sizeof instrument_status_message::fields_type");
static_assert(sizeof(instrument_status_message) == sizeof(gtp_level2mbo::message_header) + 27, "unexpected sizeof instrument_status_message");

#pragma pack(pop)
}
