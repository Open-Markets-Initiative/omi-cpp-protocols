#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Nyse.NyseConsolidated.DailyTaqTradeLuld.Csv.v4.3: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace nyse::nyseconsolidated::dailytaqtradeluld::csv::v4_3 {

// Trade Luld: a data line of the model, its fields typed as the model states them
struct TradeLuld {
    // Time: nanoseconds since midnight, America/New_York
    ::scaled::delimited::values::Required<std::uint64_t> time;
    // Sequence Number: an integer
    ::scaled::delimited::values::Required<std::int64_t> sequence_number;
    // Source: text
    ::scaled::delimited::values::Required<std::string_view> source;
    // Symbol: text
    ::scaled::delimited::values::Required<std::string_view> symbol;
    // Low Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> low_price;
    static constexpr int low_price_places = 6;
    // High Price: a decimal, the integer of its 6 places
    ::scaled::delimited::values::Required<std::int64_t> high_price;
    static constexpr int high_price_places = 6;
    // LULD Price Band Indicator: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> luld_price_band_indicator;
    // Reference Price: a decimal, the integer of its 6 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> reference_price;
    static constexpr int reference_price_places = 6;
    // Num Extensions: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> num_extensions;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        time.reset();
        sequence_number.reset();
        source.reset();
        symbol.reset();
        low_price.reset();
        high_price.reset();
        luld_price_band_indicator.reset();
        reference_price.reset();
        num_extensions.reset();
    }

    // Time on a day: its nanoseconds since midnight, America/New_York, as UTC Unix nanoseconds
    std::int64_t time_utc(const ::scaled::delimited::calendar::Day& day) const {
        return ::scaled::delimited::calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(time.value()));
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "TradeLuld{";
        out << "time=";
        ::scaled::delimited::values::print(out, time, [](std::ostream& to, const std::uint64_t value) { ::scaled::delimited::calendar::print(to, value, 1, "America/New_York"); });
        out << ", sequence_number=";
        ::scaled::delimited::values::print(out, sequence_number, ::scaled::delimited::values::integer);
        out << ", source=";
        ::scaled::delimited::values::print(out, source, ::scaled::delimited::values::text);
        out << ", symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", low_price=";
        ::scaled::delimited::values::print(out, low_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, low_price_places); });
        out << ", high_price=";
        ::scaled::delimited::values::print(out, high_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, high_price_places); });
        out << ", luld_price_band_indicator=";
        ::scaled::delimited::values::print(out, luld_price_band_indicator, ::scaled::delimited::values::text);
        out << ", reference_price=";
        ::scaled::delimited::values::print(out, reference_price, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, reference_price_places); });
        out << ", num_extensions=";
        ::scaled::delimited::values::print(out, num_extensions, ::scaled::delimited::values::integer);
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const TradeLuld& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = TradeLuld;

}