#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqTrades.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqtrades::csv::v4_3 {

// Trade: a data line of the model, its fields typed as the model states them
struct Trade {
    // Time: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> time;
    // Exchange: text
    ::scaled::delimited::values::Required<std::string_view> exchange;
    // Symbol: text
    ::scaled::delimited::values::Required<std::string_view> symbol;
    // Sale Condition: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> sale_condition;
    // Trade Volume: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> trade_volume;
    static constexpr int trade_volume_places = 6;
    // Trade Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> trade_price;
    static constexpr int trade_price_places = 6;
    // Trade Stop Stock Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> trade_stop_stock_indicator;
    // Trade Correction Indicator: text
    ::scaled::delimited::values::Required<std::string_view> trade_correction_indicator;
    // Sequence Number: an integer
    ::scaled::delimited::values::Required<std::int64_t> sequence_number;
    // Trade Id: text
    ::scaled::delimited::values::Required<std::string_view> trade_id;
    // Source of Trade: text
    ::scaled::delimited::values::Required<std::string_view> source_of_trade;
    // Trade Reporting Facility: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> trade_reporting_facility;
    // Participant Timestamp: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> participant_timestamp;
    // Trade Reporting Facility TRF Timestamp: nanoseconds since midnight, America/New_York; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::uint64_t> trade_reporting_facility_trf_timestamp;
    // Trade Through Exempt Indicator: an integer
    ::scaled::delimited::values::Required<std::int64_t> trade_through_exempt_indicator;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        time.reset();
        exchange.reset();
        symbol.reset();
        sale_condition.reset();
        trade_volume.reset();
        trade_price.reset();
        trade_stop_stock_indicator.reset();
        trade_correction_indicator.reset();
        sequence_number.reset();
        trade_id.reset();
        source_of_trade.reset();
        trade_reporting_facility.reset();
        participant_timestamp.reset();
        trade_reporting_facility_trf_timestamp.reset();
        trade_through_exempt_indicator.reset();
    }

    // Time on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t time_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time.value()));
    }

    // Participant Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t participant_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(participant_timestamp.value()));
    }

    // Trade Reporting Facility TRF Timestamp on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds;
    // none where the line leaves it empty
    std::optional<std::int64_t> trade_reporting_facility_trf_timestamp_utc(const ::scaled::delimited::calendar::Day& day) const {
        if (!trade_reporting_facility_trf_timestamp.has_value()) {
            return std::nullopt;
        }
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(trade_reporting_facility_trf_timestamp.value()));
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "Trade{";
        out << "time=";
        ::scaled::delimited::values::print(out, time, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", exchange=";
        ::scaled::delimited::values::print(out, exchange, ::scaled::delimited::values::text);
        out << ", symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", sale_condition=";
        ::scaled::delimited::values::print(out, sale_condition, ::scaled::delimited::values::text);
        out << ", trade_volume=";
        ::scaled::delimited::values::print(out, trade_volume, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, trade_volume_places); });
        out << ", trade_price=";
        ::scaled::delimited::values::print(out, trade_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, trade_price_places); });
        out << ", trade_stop_stock_indicator=";
        ::scaled::delimited::values::print(out, trade_stop_stock_indicator, ::scaled::delimited::values::text);
        out << ", trade_correction_indicator=";
        ::scaled::delimited::values::print(out, trade_correction_indicator, ::scaled::delimited::values::text);
        out << ", sequence_number=";
        ::scaled::delimited::values::print(out, sequence_number, ::scaled::delimited::values::integer);
        out << ", trade_id=";
        ::scaled::delimited::values::print(out, trade_id, ::scaled::delimited::values::text);
        out << ", source_of_trade=";
        ::scaled::delimited::values::print(out, source_of_trade, ::scaled::delimited::values::text);
        out << ", trade_reporting_facility=";
        ::scaled::delimited::values::print(out, trade_reporting_facility, ::scaled::delimited::values::text);
        out << ", participant_timestamp=";
        ::scaled::delimited::values::print(out, participant_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", trade_reporting_facility_trf_timestamp=";
        ::scaled::delimited::values::print(out, trade_reporting_facility_trf_timestamp, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", trade_through_exempt_indicator=";
        ::scaled::delimited::values::print(out, trade_through_exempt_indicator, ::scaled::delimited::values::integer);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const Trade& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = Trade;

}