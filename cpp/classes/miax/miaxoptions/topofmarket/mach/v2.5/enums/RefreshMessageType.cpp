#include "RefreshMessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(RefreshMessageType value) {
    switch (value) {
        case RefreshMessageType::SimpleSeriesUpdateRefresh: return "Simple Series Update Refresh";
        case RefreshMessageType::SimpleTopOfMarketRefresh: return "Simple Top Of Market Refresh";
        case RefreshMessageType::UnderlyingTradingStatusRefresh: return "Underlying Trading Status Refresh";
        case RefreshMessageType::SystemStateRefresh: return "System State Refresh";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RefreshMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
