#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// Indicates if the market participant firm qualifies as a Primary Market Maker in accordance
// with Nasdaq marketplace rules
enum class PrimaryMarketMaker : char {
    PrimaryMarketMaker = 'Y',    // Primary Market Maker
    NonPrimaryMarketMaker = 'N', // Non Primary Market Maker
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PrimaryMarketMaker value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PrimaryMarketMaker value);

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
