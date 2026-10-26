#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates if the market participant firm qualifies as a Primary Market Maker in accordance
// with NASDAQ marketplace rules
enum class PrimaryMarketMaker : char {
    Primary = 'Y',    // Primary
    NonPrimary = 'N', // Non Primary
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PrimaryMarketMaker value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PrimaryMarketMaker value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
