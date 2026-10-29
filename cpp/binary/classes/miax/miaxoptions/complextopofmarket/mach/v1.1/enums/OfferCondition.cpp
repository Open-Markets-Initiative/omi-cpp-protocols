#include "OfferCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(OfferCondition value) {
    switch (value) {
        case OfferCondition::Regular: return "Regular";
        case OfferCondition::TradingHalt: return "Trading Halt";
        case OfferCondition::Wide: return "Wide";
        case OfferCondition::SimpleAuction: return "Simple Auction";
        case OfferCondition::ComplexAuction: return "Complex Auction";
        case OfferCondition::SimpleMarketProtection: return "Simple Market Protection";
        case OfferCondition::LegMarketProtection: return "Leg Market Protection";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OfferCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
