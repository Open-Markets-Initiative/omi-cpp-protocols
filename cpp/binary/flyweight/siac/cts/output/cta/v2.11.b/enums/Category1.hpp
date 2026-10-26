#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Settlement Type
enum class Category1 : char {
    RegularSettlement = ' ',        // Regular Settlement
    CashTradeSameDayClearing = 'C', // Cash Trade Same Day Clearing
    Reserved = 'N',                 // Reserved
    Seller = 'R',                   // Seller
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Category1 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Category1 value);

} // namespace siac::cts::output::cta::v2_11_b
