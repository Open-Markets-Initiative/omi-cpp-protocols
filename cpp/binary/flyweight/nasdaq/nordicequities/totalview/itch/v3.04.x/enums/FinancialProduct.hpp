#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Type of financial product
enum class FinancialProduct : std::uint8_t {
    Stock = 1,                 // Stock
    EquityWarrant = 2,         // Equity Warrant
    EquityRight = 3,           // Equity Right
    Bond = 4,                  // Bond
    LotteryBondSeries = 6,     // Lottery Bond Series
    Convertible = 7,           // Convertible
    Warrant = 8,               // Warrant
    UnitTrustCertificate = 11, // Unit Trust Certificate
    IndexFundUnit = 12,        // Index Fund Unit
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinancialProduct value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinancialProduct value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
