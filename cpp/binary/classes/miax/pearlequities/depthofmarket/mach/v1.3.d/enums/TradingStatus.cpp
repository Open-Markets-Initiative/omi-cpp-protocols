#include "TradingStatus.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::PreOpen: return "Pre Open";
        case TradingStatus::Trading: return "Trading";
        case TradingStatus::Halt: return "Halt";
        case TradingStatus::OperationalHalt: return "Operational Halt";
        case TradingStatus::Closed: return "Closed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
