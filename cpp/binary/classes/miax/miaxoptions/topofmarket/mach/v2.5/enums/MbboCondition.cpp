#include "MbboCondition.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(MbboCondition value) {
    switch (value) {
        case MbboCondition::Regular: return "Regular";
        case MbboCondition::PublicCustomerInterest: return "Public Customer Interest";
        case MbboCondition::NotFirm: return "Not Firm";
        case MbboCondition::Reserved: return "Reserved";
        case MbboCondition::TradingHalt: return "Trading Halt";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MbboCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
