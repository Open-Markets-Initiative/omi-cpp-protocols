#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqCtaAdmin.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqctaadmin::csv::v4_3 {

// Cta Admin: a data line of the model, its fields typed as the model states them
struct CtaAdmin {
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
    // Participant Identifier: text
    ::scaled::delimited::values::Required<std::string_view> participant_identifier;
    // Participant Timestamp: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> participant_timestamp;
    // Financial Status: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> financial_status;
    // Currency Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> currency_indicator;
    // Security Status: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> security_status;
    // Halt Reason: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> halt_reason;
    // Related Security Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> related_security_indicator;
    // Common Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> common_indicator;
    // Last Price: a decimal, the integer of its 6 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> last_price;
    static constexpr int last_price_places = 6;
    // Status Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> status_indicator;
    // High Indication Price/Upper Limit Price Band: a decimal, the integer of its 6 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> high_indication_priceupper_limit_price_band;
    static constexpr int high_indication_priceupper_limit_price_band_places = 6;
    // Low Indication Price/LowerL imit Price Band: a decimal, the integer of its 6 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> low_indication_pricelowerl_imit_price_band;
    static constexpr int low_indication_pricelowerl_imit_price_band_places = 6;
    // Buy Volume: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> buy_volume;
    // Sell Volume: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> sell_volume;
    // Short Sale Restriction Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> short_sale_restriction_indicator;
    // Limit Up/Limit Down Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> limit_uplimit_down_indicator;
    // Market Wide Circuit Breaker Decline Level 1: a decimal, the integer of its 2 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> market_wide_circuit_breaker_decline_level_1;
    static constexpr int market_wide_circuit_breaker_decline_level_1_places = 2;
    // Market Wide Circuit Breaker Decline Level 2: a decimal, the integer of its 2 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> market_wide_circuit_breaker_decline_level_2;
    static constexpr int market_wide_circuit_breaker_decline_level_2_places = 2;
    // Market Wide Circuit Breaker Decline Level 3: a decimal, the integer of its 2 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> market_wide_circuit_breaker_decline_level_3;
    static constexpr int market_wide_circuit_breaker_decline_level_3_places = 2;
    // Market Wide Circuit Breaker Status: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> market_wide_circuit_breaker_status;
    // Message Text: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> message_text;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        timestamp.reset();
        symbol.reset();
        message_category.reset();
        message_type.reset();
        message_sequence_number.reset();
        participant_identifier.reset();
        participant_timestamp.reset();
        financial_status.reset();
        currency_indicator.reset();
        security_status.reset();
        halt_reason.reset();
        related_security_indicator.reset();
        common_indicator.reset();
        last_price.reset();
        status_indicator.reset();
        high_indication_priceupper_limit_price_band.reset();
        low_indication_pricelowerl_imit_price_band.reset();
        buy_volume.reset();
        sell_volume.reset();
        short_sale_restriction_indicator.reset();
        limit_uplimit_down_indicator.reset();
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

    // Participant Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t participant_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(participant_timestamp.value()));
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "CtaAdmin{";
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
        out << ", participant_identifier=";
        ::scaled::delimited::values::print(out, participant_identifier, ::scaled::delimited::values::text);
        out << ", participant_timestamp=";
        ::scaled::delimited::values::print(out, participant_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", financial_status=";
        ::scaled::delimited::values::print(out, financial_status, ::scaled::delimited::values::text);
        out << ", currency_indicator=";
        ::scaled::delimited::values::print(out, currency_indicator, ::scaled::delimited::values::text);
        out << ", security_status=";
        ::scaled::delimited::values::print(out, security_status, ::scaled::delimited::values::text);
        out << ", halt_reason=";
        ::scaled::delimited::values::print(out, halt_reason, ::scaled::delimited::values::text);
        out << ", related_security_indicator=";
        ::scaled::delimited::values::print(out, related_security_indicator, ::scaled::delimited::values::text);
        out << ", common_indicator=";
        ::scaled::delimited::values::print(out, common_indicator, ::scaled::delimited::values::text);
        out << ", last_price=";
        ::scaled::delimited::values::print(out, last_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, last_price_places); });
        out << ", status_indicator=";
        ::scaled::delimited::values::print(out, status_indicator, ::scaled::delimited::values::text);
        out << ", high_indication_priceupper_limit_price_band=";
        ::scaled::delimited::values::print(out, high_indication_priceupper_limit_price_band, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, high_indication_priceupper_limit_price_band_places); });
        out << ", low_indication_pricelowerl_imit_price_band=";
        ::scaled::delimited::values::print(out, low_indication_pricelowerl_imit_price_band, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, low_indication_pricelowerl_imit_price_band_places); });
        out << ", buy_volume=";
        ::scaled::delimited::values::print(out, buy_volume, ::scaled::delimited::values::integer);
        out << ", sell_volume=";
        ::scaled::delimited::values::print(out, sell_volume, ::scaled::delimited::values::integer);
        out << ", short_sale_restriction_indicator=";
        ::scaled::delimited::values::print(out, short_sale_restriction_indicator, ::scaled::delimited::values::text);
        out << ", limit_uplimit_down_indicator=";
        ::scaled::delimited::values::print(out, limit_uplimit_down_indicator, ::scaled::delimited::values::text);
        out << ", market_wide_circuit_breaker_decline_level_1=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_decline_level_1, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, market_wide_circuit_breaker_decline_level_1_places); });
        out << ", market_wide_circuit_breaker_decline_level_2=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_decline_level_2, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, market_wide_circuit_breaker_decline_level_2_places); });
        out << ", market_wide_circuit_breaker_decline_level_3=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_decline_level_3, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, market_wide_circuit_breaker_decline_level_3_places); });
        out << ", market_wide_circuit_breaker_status=";
        ::scaled::delimited::values::print(out, market_wide_circuit_breaker_status, ::scaled::delimited::values::text);
        out << ", message_text=";
        ::scaled::delimited::values::print(out, message_text, ::scaled::delimited::values::text);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const CtaAdmin& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = CtaAdmin;

}