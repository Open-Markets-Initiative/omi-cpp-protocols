#include "MarketCondition.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(MarketCondition value) {
    switch (value) {
        case MarketCondition::NormalAuctionMarket: return "Normal Auction Market";
        case MarketCondition::CrossedMarket: return "Crossed Market";
        case MarketCondition::LockedMarket: return "Locked Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
