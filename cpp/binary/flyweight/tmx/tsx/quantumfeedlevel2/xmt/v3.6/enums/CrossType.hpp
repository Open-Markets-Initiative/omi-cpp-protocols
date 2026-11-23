// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/CrossType.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Type Of Crosses Originating From A Participating Organization Between Managed Accounts That
// Have The Same Manager
enum class CrossType : char {
    Internal = 'I',                   // Internal
    Basis = 'B',                      // Basis
    Contingent = 'C',                 // Contingent
    DerivativeRelated = 'D',          // Derivative Related
    Regular = 'R',                    // Regular
    SpecialTradingSession = 'S',      // Special Trading Session
    VolumeWeightedAveragePrice = 'V', // Volume Weighted Average Price
    DefaultTradeWasNotACross = ' ',   // Default Trade Was Not A Cross
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
