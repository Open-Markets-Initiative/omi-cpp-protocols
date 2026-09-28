#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Offset3Padding5.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/TradeDate.hpp"
#include "../types/Offset14Padding2.hpp"
#include "../types/TradSesOpenTime.hpp"
#include "../types/TransactTime.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

#pragma pack(push, 1)

// Security Group Phase 10 Message
struct security_group_phase_10_message {

    struct fields_type {
        sbe_binaryumdf::security_group security_group;
        sbe_binaryumdf::offset_3_padding_5 offset_3_padding_5;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::trading_session_id trading_session_id;
        sbe_binaryumdf::trading_session_sub_id trading_session_sub_id;
        sbe_binaryumdf::security_trading_event security_trading_event;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::offset_14_padding_2 offset_14_padding_2;
        sbe_binaryumdf::trad_ses_open_time trad_ses_open_time;
        sbe_binaryumdf::transact_time transact_time;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static security_group_phase_10_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_group_phase_10_message*>(buffer);
    }

    // parse method const
    static const security_group_phase_10_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_group_phase_10_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_group_phase_10_message::fields_type, security_group) == 0, "unexpected offset of security_group_phase_10_message::fields_type::security_group");
static_assert(offsetof(security_group_phase_10_message::fields_type, offset_3_padding_5) == 3, "unexpected offset of security_group_phase_10_message::fields_type::offset_3_padding_5");
static_assert(offsetof(security_group_phase_10_message::fields_type, match_event_indicator) == 8, "unexpected offset of security_group_phase_10_message::fields_type::match_event_indicator");
static_assert(offsetof(security_group_phase_10_message::fields_type, trading_session_id) == 9, "unexpected offset of security_group_phase_10_message::fields_type::trading_session_id");
static_assert(offsetof(security_group_phase_10_message::fields_type, trading_session_sub_id) == 10, "unexpected offset of security_group_phase_10_message::fields_type::trading_session_sub_id");
static_assert(offsetof(security_group_phase_10_message::fields_type, security_trading_event) == 11, "unexpected offset of security_group_phase_10_message::fields_type::security_trading_event");
static_assert(offsetof(security_group_phase_10_message::fields_type, trade_date) == 12, "unexpected offset of security_group_phase_10_message::fields_type::trade_date");
static_assert(offsetof(security_group_phase_10_message::fields_type, offset_14_padding_2) == 14, "unexpected offset of security_group_phase_10_message::fields_type::offset_14_padding_2");
static_assert(offsetof(security_group_phase_10_message::fields_type, trad_ses_open_time) == 16, "unexpected offset of security_group_phase_10_message::fields_type::trad_ses_open_time");
static_assert(offsetof(security_group_phase_10_message::fields_type, transact_time) == 24, "unexpected offset of security_group_phase_10_message::fields_type::transact_time");
static_assert(sizeof(security_group_phase_10_message::fields_type) == 32, "unexpected sizeof security_group_phase_10_message::fields_type");
static_assert(sizeof(security_group_phase_10_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 32, "unexpected sizeof security_group_phase_10_message");

#pragma pack(pop)
}
