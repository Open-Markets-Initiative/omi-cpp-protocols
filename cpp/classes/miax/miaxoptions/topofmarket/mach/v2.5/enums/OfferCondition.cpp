#include "OfferCondition.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(OfferCondition value) {
    switch (value) {
        case OfferCondition::Regular: return "Regular";
        case OfferCondition::PublicCustomerInterest: return "Public Customer Interest";
        case OfferCondition::NotFirm: return "Not Firm";
        case OfferCondition::Reserved: return "Reserved";
        case OfferCondition::TradingHalt: return "Trading Halt";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OfferCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
