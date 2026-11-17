// Row.hpp
#pragma once

#include <cstdint>
#include <optional>
#include <ostream>
#include <string_view>

#include "../delimited/Day.hpp"
#include "../delimited/Values.hpp"

// Memx.MemxEquities.InstrumentDirectory.Csv.v2026.10.14: its data record as a plain C++ row, which Rows.hpp reads a line onto
namespace memx::memxequities::instrumentdirectory::csv::v2026_10_14 {

// Instrument: a data line of the model, its fields typed as the model states them
struct Instrument {
    // securityId: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> securityid;
    // symbol: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> symbol;
    // symbolSfx: text; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::string_view> symbolsfx;
    // roundLot: an integer; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> roundlot;
    // isTestSymbol: a boolean; none where the line leaves it empty
    ::scaled::delimited::values::Optional<bool> istestsymbol;
    // mpv: a decimal, the integer of its 6 places; none where the line leaves it empty
    ::scaled::delimited::values::Optional<std::int64_t> mpv;
    static constexpr int mpv_places = 6;

    // every field emptied: a row is reset before a line is read onto it
    void reset() {
        securityid.reset();
        symbol.reset();
        symbolsfx.reset();
        roundlot.reset();
        istestsymbol.reset();
        mpv.reset();
    }

    // the row as name=value, a time of day on the stream's print day as the instant, ISO 8601 UTC
    void print(std::ostream& out) const {
        out << "Instrument{";
        out << "securityid=";
        ::scaled::delimited::values::print(out, securityid, ::scaled::delimited::values::integer);
        out << ", symbol=";
        ::scaled::delimited::values::print(out, symbol, ::scaled::delimited::values::text);
        out << ", symbolsfx=";
        ::scaled::delimited::values::print(out, symbolsfx, ::scaled::delimited::values::text);
        out << ", roundlot=";
        ::scaled::delimited::values::print(out, roundlot, ::scaled::delimited::values::integer);
        out << ", istestsymbol=";
        ::scaled::delimited::values::print(out, istestsymbol, ::scaled::delimited::values::boolean);
        out << ", mpv=";
        ::scaled::delimited::values::print(out, mpv, [](std::ostream& to, const std::int64_t value) { ::scaled::delimited::values::decimal(to, value, mpv_places); });
        out << '}';
    }
};

inline std::ostream& operator<<(std::ostream& out, const Instrument& row) {
    row.print(out);
    return out;
}

// the row a data line is read onto
using Row = Instrument;

}