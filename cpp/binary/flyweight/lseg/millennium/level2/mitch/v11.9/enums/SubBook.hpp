#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// Sub Book
enum class SubBook : std::uint8_t {
    RegularTrades = 0, // Regular Trades
    RfqTrades = 11,    // Rfq Trades
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SubBook value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SubBook value);

} // namespace lseg::millennium::level2::mitch::v11_9
