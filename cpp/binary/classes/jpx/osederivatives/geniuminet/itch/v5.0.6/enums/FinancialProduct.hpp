#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Product type
enum class FinancialProduct : std::uint8_t {
    Option = 1,                      // Option
    Forward = 2,                     // Forward
    Future = 3,                      // Future
    Fra = 4,                         // Fra
    Cash = 5,                        // Cash
    Payment = 6,                     // Payment
    ExchangeRate = 7,                // Exchange Rate
    InterestRateSwap = 8,            // Interest Rate Swap
    Repo = 9,                        // Repo
    SyntheticBoxLegOrReference = 10, // Synthetic Box Leg Or Reference
    Combination = 11,                // Combination
    Guarantee = 12,                  // Guarantee
    OtcGeneral = 13,                 // Otc General
    EquityWarrant = 14,              // Equity Warrant
    SecurityLending = 15,            // Security Lending
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinancialProduct value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinancialProduct value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
