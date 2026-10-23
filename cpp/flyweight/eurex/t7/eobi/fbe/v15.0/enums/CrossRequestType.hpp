#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class CrossRequestType : std::uint8_t {
    CrossAnnouncement = 1,         // Cross Announcement
    LiquidityImprovementCross = 2, // Liquidity Improvement Cross
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossRequestType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossRequestType value);

} // namespace eurex::t7::eobi::fbe::v15_0
