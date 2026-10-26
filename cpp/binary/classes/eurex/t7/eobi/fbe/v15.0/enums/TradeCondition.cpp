#include "TradeCondition.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::ImpliedTrade: return "Implied Trade";
        case TradeCondition::OutOfSequence: return "Out Of Sequence";
        case TradeCondition::MidpointPrice: return "Midpoint Price";
        case TradeCondition::TradingOnTermsOfIssue: return "Trading On Terms Of Issue";
        case TradeCondition::SpecialAuction: return "Special Auction";
        case TradeCondition::TradeAtClose: return "Trade At Close";
        case TradeCondition::Retail: return "Retail";
        case TradeCondition::AuctionVolumeDiscovery: return "Auction Volume Discovery";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
