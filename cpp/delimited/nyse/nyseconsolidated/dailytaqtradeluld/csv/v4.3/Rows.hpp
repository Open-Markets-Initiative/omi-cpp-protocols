#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Nyse.NyseConsolidated.DailyTaqTradeLuld.Csv.v4.3: delimited lines to the rows of its Parquet table
namespace nyse::nyseconsolidated::dailytaqtradeluld::csv::v4_3 {

// how the file's lines are told apart and split
constexpr char delimiter = '|';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 9;

// a data line's fields: split at the delimiter
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    ::scaled::delimited::split(line, delimiter, fields);
}

// layout DailyTaqTradeLuld.v4.3: the header a file of this layout states, and its reading
namespace variant_dailytaqtradeluld_v4_3 {

    // Layout: Time|Sequence Number|Source|Symbol|Low Price|High Price|LULD Price Band Indicator|Reference Price|Num Extensions
    constexpr std::array<std::string_view, 9> layout{ "Time", "Sequence Number", "Source", "Symbol", "Low Price", "High Price", "LULD Price Band Indicator", "Reference Price", "Num Extensions" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", '|', false, layout },
    } };

    // Trade Luld: a line of 9 fields, or as few as 6: its last 3 are optional, null where the line stops before them; onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 6, 9, "Trade Luld");
        row.time.set(static_cast<std::uint64_t>(::scaled::delimited::time_of_day(fields[0], 9, "Time")));  // Time
        row.sequence_number.set(::scaled::delimited::integer<std::int64_t>(fields[1], "Sequence Number"));  // Sequence Number
        row.source.set(fields[2]);  // Source
        row.symbol.set(fields[3]);  // Symbol
        row.low_price.data = ::scaled::delimited::decimal(fields[4], 6, "Low Price");  // Low Price
        row.high_price.data = ::scaled::delimited::decimal(fields[5], 6, "High Price");  // High Price
        if (!::scaled::delimited::at(fields, 6).empty()) {  // LULD Price Band Indicator
            row.luld_price_band_indicator.set(::scaled::delimited::at(fields, 6));
        }
        if (!::scaled::delimited::at(fields, 7).empty()) {  // Reference Price
            row.reference_price.data = ::scaled::delimited::decimal(::scaled::delimited::at(fields, 7), 6, "Reference Price");
        }
        if (!::scaled::delimited::at(fields, 8).empty()) {  // Num Extensions
            row.num_extensions.set(::scaled::delimited::integer<std::int64_t>(::scaled::delimited::at(fields, 8), "Num Extensions"));
        }
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "DailyTaqTradeLuld.v4.3" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_dailytaqtradeluld_v4_3::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Nyse.NyseConsolidated.DailyTaqTradeLuld.Csv.v4.3");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_dailytaqtradeluld_v4_3::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}