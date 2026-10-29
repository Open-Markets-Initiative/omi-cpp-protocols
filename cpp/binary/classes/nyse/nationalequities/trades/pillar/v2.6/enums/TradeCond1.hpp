#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// Settlement related conditions.
enum class TradeCond1 : char {
    RegularSale = '@',        // Regular Sale
    Cash = 'C',               // Cash
    RegularSaleTrfOnly = ' ', // Regular Sale Trf Only
    SellerTrfOnly = 'R',      // Seller Trf Only
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond1 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond1 value);

} // namespace nyse::nationalequities::trades::pillar::v2_6
