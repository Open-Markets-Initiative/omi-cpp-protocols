#include "BidCondition.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(BidCondition value) {
    switch (value) {
        case BidCondition::Regular: return "Regular";
        case BidCondition::PublicCustomerInterest: return "Public Customer Interest";
        case BidCondition::NotFirm: return "Not Firm";
        case BidCondition::Reserved: return "Reserved";
        case BidCondition::TradingHalt: return "Trading Halt";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BidCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
