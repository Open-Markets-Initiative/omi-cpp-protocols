// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/ProductType.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Product Type For A Symbol
enum class ProductType : char {
    Debenture = 'B',  // Debenture
    Equity = 'E',     // Equity
    MutualFund = 'M', // Mutual Fund
    Etf = 'F',        // Etf
    UsEquity = 'U',   // Us Equity
    Bond = 'O',       // Bond
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ProductType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ProductType value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
