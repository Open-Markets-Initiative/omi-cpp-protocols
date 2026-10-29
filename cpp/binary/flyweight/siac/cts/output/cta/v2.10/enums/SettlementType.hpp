#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Category 1: Settlement Type
enum class SettlementType : char {
    RegularSettlement = ' ', // Regular Settlement
    CashTrade = 'C',         // Cash Trade
    NextDayTrade = 'N',      // Next Day Trade
    Seller = 'R',            // Seller
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlementType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlementType value);

} // namespace siac::cts::output::cta::v2_10
