#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Used for Settlement Type information
enum class SettlementType : char {
    RegularSettlement = '@', // Regular Settlement
    CashSettlement = 'C',    // Cash Settlement
    NextDaySettlement = 'N', // Next Day Settlement
    SellerSettlement = 'R',  // Seller Settlement
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlementType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlementType value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
