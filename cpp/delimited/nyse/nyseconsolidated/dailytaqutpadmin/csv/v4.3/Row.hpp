#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqUtpAdmin.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqutpadmin::csv::v4_3 {

// Utp Admin: a data line of the model, its fields typed as the model states them
struct UtpAdmin {
    // Timestamp: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> timestamp;
    // Symbol: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> symbol;
    // Message Category: text
    ::scaled::delimited::values::Required<std::string_view> message_category;
    // Message Type: text
    ::scaled::delimited::values::Required<std::string_view> message_type;
    // Message Sequence Number: an integer
    ::scaled::delimited::values::Required<std::int64_t> message_sequence_number;
    // Market Center Originator ID: text
    ::scaled::delimited::values::Required<std::string_view> market_center_originator_id;
    // Sub Market Center Originator ID: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> sub_market_center_originator_id;
    // Participant Timestamp: nanoseconds since midnight, America/New_York; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::uint64_t> participant_timestamp;
    // Financial Status: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> financial_status;
    // Short Sale Treshold Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> short_sale_treshold_indicator;
    // Short Sale Restriction Indicator: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> short_sale_restriction_indicator;
    // Trading Action Code: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> trading_action_code;
    // Trading Action Sequence Number: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> trading_action_sequence_number;
    // Trading Action Timestamp: nanoseconds since midnight, America/New_York; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::uint64_t> trading_action_timestamp;
    // Trading Action Reason: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> trading_action_reason;
    // LULD Lower Limit Price Band: a decimal, the integer of its 6 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> luld_lower_limit_price_band;
    static constexpr int luld_lower_limit_price_band_places = 6;
    // LULD Upper Limit Price Band: a decimal, the integer of its 6 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> luld_upper_limit_price_band;
    static constexpr int luld_upper_limit_price_band_places = 6;
    // LULDPrice Band Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> luldprice_band_indicator;
    // Market Wide Circuit Breaker Decline Level 1: a decimal, the integer of its 2 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> market_wide_circuit_breaker_decline_level_1;
    static constexpr int market_wide_circuit_breaker_decline_level_1_places = 2;
    // Market Wide Circuit Breaker Decline Level 2: a decimal, the integer of its 2 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> market_wide_circuit_breaker_decline_level_2;
    static constexpr int market_wide_circuit_breaker_decline_level_2_places = 2;
    // Market Wide Circuit Breaker Decline Level 3: a decimal, the integer of its 2 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> market_wide_circuit_breaker_decline_level_3;
    static constexpr int market_wide_circuit_breaker_decline_level_3_places = 2;
    // Market Wide Circuit Breaker Status: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> market_wide_circuit_breaker_status;
    // Message Text: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> message_text;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        timestamp.reset();
        symbol.reset();
        message_category.reset();
        message_type.reset();
        message_sequence_number.reset();
        market_center_originator_id.reset();
        sub_market_center_originator_id.reset();
        participant_timestamp.reset();
        financial_status.reset();
        short_sale_treshold_indicator.reset();
        short_sale_restriction_indicator.reset();
        trading_action_code.reset();
        trading_action_sequence_number.reset();
        trading_action_timestamp.reset();
        trading_action_reason.reset();
        luld_lower_limit_price_band.reset();
        luld_upper_limit_price_band.reset();
        luldprice_band_indicator.reset();
        market_wide_circuit_breaker_decline_level_1.reset();
        market_wide_circuit_breaker_decline_level_2.reset();
        market_wide_circuit_breaker_decline_level_3.reset();
        market_wide_circuit_breaker_status.reset();
        message_text.reset();
    }

    // Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp.value()));
    }

    // Participant Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds;
    // none where the line leaves it empty
    std::optional<std::int64_t> participant_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        if (!participant_timestamp.has_value()) {
            return std::nullopt;
        }
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(participant_timestamp.value()));
    }

    // Trading Action Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds;
    // none where the line leaves it empty
    std::optional<std::int64_t> trading_action_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        if (!trading_action_timestamp.has_value()) {
            return std::nullopt;
        }
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(trading_action_timestamp.value()));
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "UtpAdmin{";
        out << "timestamp=";
        ::scaled::delimited::values::print(out, timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", message_category=";
        ::scaled::delimited::values::print(out, message_category, ::scaled::delimited::values::text);
        out << ", message_type=";
        ::scaled::delimited::values::print(out, message_type, ::scaled::delimited::values::text);
        out << ", message_sequence_number=";
        ::scaled::delimited::values::print(out, message_sequence_number, ::scaled::delimited::values::integer);
        out << ", market_center_originator_id=";
        ::scaled::delimited::values::print(out, market_center_originator_id, ::scaled::delimited::values::text);
        out << ", sub_market_center_originator_id=";
        ::scaled::delimited::values::print(out, sub_market_center_originator_id, ::scaled::delimited::values::text);
        out << ", participant_timestamp=";
        ::scaled::delimited::values::print(out, participant_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", financial_status=";
        ::scaled::delimited::values::print(out, financial_status, ::scaled::delimited::values::text);
        out << ", short_sale_treshold_indicator=";
        ::scaled::delimited::values::print(out, short_sale_treshold_indicator, ::scaled::delimited::values::text);
        out << ", short_sale_restriction_indicator=";
        ::scaled::delimited::values::print(out, short_sale_restriction_indicator, ::scaled::delimited::values::integer);
        out << ", trading_action_code=";
        ::scaled::delimited::values::print(out, trading_action_code, ::scaled::delimited::values::text);
        out << ", trading_action_sequence_number=";
        ::scaled::delimited::values::print(out, trading_action_sequence_number, ::scaled::delimited::values::integer);
        out << ", trading_action_timestamp=";
        ::scaled::delimited::values::print(out, trading_action_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", trading_action_reason=";
        ::scaled::delimited::values::print(out, trading_action_reason, ::scaled::delimited::values::text);
        out << ", luld_lower_limit_price_band=";
        ::scaled::delimited::values::print(out, luld_lower_limit_price_band, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, luld_lower_limit_price_band_places); });
        out << ", luld_upper_limit_price_band=";
        ::scaled::delimited::values::print(out, luld_upper_limit_price_band, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, luld_upper_limit_price_band_places); });
        out << ", luldprice_band_indicator=";
        ::scaled::delimited::values::print(out, luldprice_band_indicator, ::scaled::delimited::values::text);
        out << ", market_wide_circuit_breaker_decline_level_1=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_decline_level_1, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, market_wide_circuit_breaker_decline_level_1_places); });
        out << ", market_wide_circuit_breaker_decline_level_2=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_decline_level_2, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, market_wide_circuit_breaker_decline_level_2_places); });
        out << ", market_wide_circuit_breaker_decline_level_3=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_decline_level_3, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, market_wide_circuit_breaker_decline_level_3_places); });
        out << ", market_wide_circuit_breaker_status=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_status, ::scaled::delimited::values::integer);
        out << ", message_text=";
        ::scaled::delimited::values::print(out, message_text, ::scaled::delimited::values::text);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const UtpAdmin& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = UtpAdmin;

}