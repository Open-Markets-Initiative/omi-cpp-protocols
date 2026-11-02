#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

#include "../delimited/Scanner.hpp"

// Memx.MemxEquities.InstrumentDirectory.Csv.v2026.10.14: delimited lines to the rows of its Parquet table
namespace memx::memxequities::instrumentdirectory::csv::v2026_10_14 {

// how the file's lines are told apart and split
constexpr char delimiter = ',';
constexpr char terminator = '\n';
// the table's columns, as many as its data record's fields
constexpr std::size_t columns = 6;

// a data line's fields: split at the delimiter outside the quote '"', a doubled quote inside quotes one quote
constexpr char quote = '"';
inline void split(const std::string_view line, ::scaled::delimited::Fields& fields) {
    static thread_local std::deque<std::string> unquoted;
    ::scaled::delimited::split(line, delimiter, quote, fields, unquoted);
}

// layout Instrument.v2026.10.14: the header a file of this layout states, and its reading
namespace variant_instrument_v2026_10_14 {

    // Layout: securityId,symbol,symbolSfx,roundLot,isTestSymbol,mpv
    constexpr std::array<std::string_view, 6> layout{ "securityId", "symbol", "symbolSfx", "roundLot", "isTestSymbol", "mpv" };

    // every header line the file states before its data
    constexpr std::array<::scaled::delimited::Expected, 1> header{ {
        ::scaled::delimited::Expected{ "Layout", "", ',', false, layout, '"' },
    } };

    // Instrument: a line of 6 fields, onto a row
    template <typename Row>
    void read(const ::scaled::delimited::Fields& fields, Row& row) {
        ::scaled::delimited::expect(fields, 6, "Instrument");
        if (!fields[0].empty()) {  // securityId
            row.securityid.set(::scaled::delimited::integer<std::int64_t>(fields[0], "securityId"));
        }
        if (!fields[1].empty()) {  // symbol
            row.symbol.set(fields[1]);
        }
        if (!fields[2].empty()) {  // symbolSfx
            row.symbolsfx.set(fields[2]);
        }
        if (!fields[3].empty()) {  // roundLot
            row.roundlot.set(::scaled::delimited::integer<std::int64_t>(fields[3], "roundLot"));
        }
        if (!fields[4].empty()) {  // isTestSymbol
            row.istestsymbol.set(::scaled::delimited::boolean(fields[4], "true", "false", "isTestSymbol") != 0);
        }
        if (!fields[5].empty()) {  // mpv
            row.mpv.data = ::scaled::delimited::integer<std::int64_t>(fields[5], "mpv");
        }
    }
}

// the layout variants, by the index select gives
constexpr std::array<std::string_view, 1> variants{ "Instrument.v2026.10.14" };

// the variant whose header the file's header lines state exactly; refused naming the closest variant's first difference
inline std::size_t select(const std::vector<std::string>& lines) {
    const std::array<::scaled::delimited::Difference, 1> differences{ {
        ::scaled::delimited::compare(lines, variant_instrument_v2026_10_14::header, true),
    } };
    return ::scaled::delimited::select(differences, variants, "Memx.MemxEquities.InstrumentDirectory.Csv.v2026.10.14");
}

// a data line onto a row, by the selected variant
template <typename Row>
void read(const std::size_t variant, const ::scaled::delimited::Fields& fields, Row& row) {
    switch (variant) {
        case 0: variant_instrument_v2026_10_14::read(fields, row); return;
        default: throw ::scaled::delimited::Error{ "layout variant " + std::to_string(variant) + " is not in the model" };
    }
}

}