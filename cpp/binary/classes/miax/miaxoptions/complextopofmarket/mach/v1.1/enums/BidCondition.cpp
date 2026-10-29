#include "BidCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(BidCondition value) {
    switch (value) {
        case BidCondition::Regular: return "Regular";
        case BidCondition::TradingHalt: return "Trading Halt";
        case BidCondition::Wide: return "Wide";
        case BidCondition::SimpleAuction: return "Simple Auction";
        case BidCondition::ComplexAuction: return "Complex Auction";
        case BidCondition::SimpleMarketProtection: return "Simple Market Protection";
        case BidCondition::LegMarketProtection: return "Leg Market Protection";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BidCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
