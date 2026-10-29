#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Underlying Asset Type of this instrument
enum class UnderlyingAssetType : char {
    EquityIndex = 'E',          // Equity Index
    CommodityAgriculture = 'A', // Commodity Agriculture
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnderlyingAssetType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnderlyingAssetType value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
