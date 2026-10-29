#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes the Nasdaq market system that generated the trade report message
enum class OriginatingMarketCenterIdentifier : char {
    Nasdaq = 'Q',      // Nasdaq
    TrfCarteret = 'L', // Trf Carteret
    TrfChicago = '2',  // Trf Chicago
    Bx = 'B',          // Bx
    Psx = 'X',         // Psx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OriginatingMarketCenterIdentifier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OriginatingMarketCenterIdentifier value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
