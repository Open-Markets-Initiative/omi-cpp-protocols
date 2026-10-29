#include "UnderlyingAssetType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(UnderlyingAssetType value) {
    switch (value) {
        case UnderlyingAssetType::EquityIndex: return "Equity Index";
        case UnderlyingAssetType::CommodityAgriculture: return "Commodity Agriculture";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnderlyingAssetType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
