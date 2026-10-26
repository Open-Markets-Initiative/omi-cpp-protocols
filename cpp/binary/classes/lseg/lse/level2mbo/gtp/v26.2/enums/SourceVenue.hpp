#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Venue from which market data is received for the instrument.
enum class SourceVenue : std::uint16_t {
    LondonStockExchange = 1, // London Stock Exchange
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SourceVenue value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SourceVenue value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
