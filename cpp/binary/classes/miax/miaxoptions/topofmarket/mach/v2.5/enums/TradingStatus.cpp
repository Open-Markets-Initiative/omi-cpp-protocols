#include "TradingStatus.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::Halted: return "Halted";
        case TradingStatus::Resumed: return "Resumed";
        case TradingStatus::Opened: return "Opened";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
