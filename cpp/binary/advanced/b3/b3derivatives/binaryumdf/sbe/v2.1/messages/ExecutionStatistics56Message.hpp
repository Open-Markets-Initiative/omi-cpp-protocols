#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/VwapPx.hpp"
#include "../types/NetChgPrevDay.hpp"
#include "../types/NumberOfTrades.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_1;

#pragma pack(push, 1)

// Execution Statistics 56 Message
struct execution_statistics_56_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::trading_session_id trading_session_id;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::trade_volume trade_volume;
        sbe_binaryumdf::vwap_px vwap_px;
        sbe_binaryumdf::net_chg_prev_day net_chg_prev_day;
        sbe_binaryumdf::number_of_trades number_of_trades;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static execution_statistics_56_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_statistics_56_message*>(buffer);
    }

    // parse method const
    static const execution_statistics_56_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_statistics_56_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_statistics_56_message::fields_type, security_id) == 0, "unexpected offset of execution_statistics_56_message::fields_type::security_id");
static_assert(offsetof(execution_statistics_56_message::fields_type, match_event_indicator) == 8, "unexpected offset of execution_statistics_56_message::fields_type::match_event_indicator");
static_assert(offsetof(execution_statistics_56_message::fields_type, trading_session_id) == 9, "unexpected offset of execution_statistics_56_message::fields_type::trading_session_id");
static_assert(offsetof(execution_statistics_56_message::fields_type, trade_date) == 10, "unexpected offset of execution_statistics_56_message::fields_type::trade_date");
static_assert(offsetof(execution_statistics_56_message::fields_type, trade_volume) == 12, "unexpected offset of execution_statistics_56_message::fields_type::trade_volume");
static_assert(offsetof(execution_statistics_56_message::fields_type, vwap_px) == 20, "unexpected offset of execution_statistics_56_message::fields_type::vwap_px");
static_assert(offsetof(execution_statistics_56_message::fields_type, net_chg_prev_day) == 28, "unexpected offset of execution_statistics_56_message::fields_type::net_chg_prev_day");
static_assert(offsetof(execution_statistics_56_message::fields_type, number_of_trades) == 36, "unexpected offset of execution_statistics_56_message::fields_type::number_of_trades");
static_assert(offsetof(execution_statistics_56_message::fields_type, md_entry_timestamp) == 40, "unexpected offset of execution_statistics_56_message::fields_type::md_entry_timestamp");
static_assert(offsetof(execution_statistics_56_message::fields_type, rpt_seq) == 48, "unexpected offset of execution_statistics_56_message::fields_type::rpt_seq");
static_assert(sizeof(execution_statistics_56_message::fields_type) == 52, "unexpected sizeof execution_statistics_56_message::fields_type");
static_assert(sizeof(execution_statistics_56_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 52, "unexpected sizeof execution_statistics_56_message");

#pragma pack(pop)
}
