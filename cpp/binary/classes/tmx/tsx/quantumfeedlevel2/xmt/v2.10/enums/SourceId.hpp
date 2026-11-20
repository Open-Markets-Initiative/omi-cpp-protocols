// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/SourceId.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Source Id of the Business message
enum class SourceId : char {
    NonSourceRelated = '0', // Non Source Related
    Tsx = 'Q',              // TSX
    TsxVenture = 'V',       // TSX Venture
    Alpha = 'A',            // Alpha
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SourceId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SourceId value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
