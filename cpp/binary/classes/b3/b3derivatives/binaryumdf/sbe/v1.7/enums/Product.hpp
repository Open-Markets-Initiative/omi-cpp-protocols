#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// product
enum class Product : std::uint8_t {
    Commodity = 2,          // Commodity
    Corporate = 3,          // Corporate
    Currency = 4,           // Currency
    Equity = 5,             // Equity
    Government = 6,         // Government
    Index = 7,              // Index
    EconomicIndicator = 15, // Economic Indicator
    Multileg = 16,          // Multileg
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Product value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Product value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
