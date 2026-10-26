#include "MatchType.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(MatchType value) {
    switch (value) {
        case MatchType::ConfirmedTradeReport: return "Confirmed Trade Report";
        case MatchType::CrossAuction: return "Cross Auction";
        case MatchType::CallAuction: return "Call Auction";
        case MatchType::LiquidityImprovementCross: return "Liquidity Improvement Cross";
        case MatchType::ContinuousAuction: return "Continuous Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MatchType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
