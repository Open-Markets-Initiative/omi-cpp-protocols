// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/SettlementTerms.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Settlement Terms Associated With The Order
enum class SettlementTerms : char {
    Cash = 'C',                // Cash
    Nn = 'N',                  // Nn
    Ms = 'M',                  // Ms
    Ct = 'T',                  // Ct
    ValidSettlementDate = 'D', // Valid Settlement Date
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlementTerms value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlementTerms value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
