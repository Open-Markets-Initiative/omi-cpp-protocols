#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/TradeDate.hpp"
#include "../types/Offset14Padding2.hpp"
#include "../types/TradSesOpenTime.hpp"
#include "../types/TransactTime.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_9;

#pragma pack(push, 1)

// Security Status 3 Message
struct security_status_3_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::trading_session_id trading_session_id;
        sbe_binaryumdf::security_trading_status security_trading_status;
        sbe_binaryumdf::security_trading_event security_trading_event;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::offset_14_padding_2 offset_14_padding_2;
        sbe_binaryumdf::trad_ses_open_time trad_ses_open_time;
        sbe_binaryumdf::transact_time transact_time;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static security_status_3_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_status_3_message*>(buffer);
    }

    // parse method const
    static const security_status_3_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_status_3_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_status_3_message::fields_type, security_id) == 0, "unexpected offset of security_status_3_message::fields_type::security_id");
static_assert(offsetof(security_status_3_message::fields_type, match_event_indicator) == 8, "unexpected offset of security_status_3_message::fields_type::match_event_indicator");
static_assert(offsetof(security_status_3_message::fields_type, trading_session_id) == 9, "unexpected offset of security_status_3_message::fields_type::trading_session_id");
static_assert(offsetof(security_status_3_message::fields_type, security_trading_status) == 10, "unexpected offset of security_status_3_message::fields_type::security_trading_status");
static_assert(offsetof(security_status_3_message::fields_type, security_trading_event) == 11, "unexpected offset of security_status_3_message::fields_type::security_trading_event");
static_assert(offsetof(security_status_3_message::fields_type, trade_date) == 12, "unexpected offset of security_status_3_message::fields_type::trade_date");
static_assert(offsetof(security_status_3_message::fields_type, offset_14_padding_2) == 14, "unexpected offset of security_status_3_message::fields_type::offset_14_padding_2");
static_assert(offsetof(security_status_3_message::fields_type, trad_ses_open_time) == 16, "unexpected offset of security_status_3_message::fields_type::trad_ses_open_time");
static_assert(offsetof(security_status_3_message::fields_type, transact_time) == 24, "unexpected offset of security_status_3_message::fields_type::transact_time");
static_assert(offsetof(security_status_3_message::fields_type, rpt_seq) == 32, "unexpected offset of security_status_3_message::fields_type::rpt_seq");
static_assert(sizeof(security_status_3_message::fields_type) == 36, "unexpected sizeof security_status_3_message::fields_type");
static_assert(sizeof(security_status_3_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 36, "unexpected sizeof security_status_3_message");

#pragma pack(pop)
}
