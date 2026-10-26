#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Qualifier of the trade.
enum class TradeQualifier : char {
    Na = ' ',                   // Na
    ClosingPriceCrossCpx = 'C', // Closing Price Cross Cpx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeQualifier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeQualifier value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
