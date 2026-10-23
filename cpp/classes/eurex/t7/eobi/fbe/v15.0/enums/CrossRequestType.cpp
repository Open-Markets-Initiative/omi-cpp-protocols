#include "CrossRequestType.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(CrossRequestType value) {
    switch (value) {
        case CrossRequestType::CrossAnnouncement: return "Cross Announcement";
        case CrossRequestType::LiquidityImprovementCross: return "Liquidity Improvement Cross";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossRequestType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
