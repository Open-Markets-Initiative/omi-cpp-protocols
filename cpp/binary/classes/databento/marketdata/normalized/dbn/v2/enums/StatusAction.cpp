// Databento.MarketData.Normalized.Dbn.v2: enums/StatusAction.cpp
#include "StatusAction.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

std::string_view to_string(StatusAction value) {
    switch (value) {
        case StatusAction::None: return "None";
        case StatusAction::PreOpen: return "Pre Open";
        case StatusAction::PreCross: return "Pre Cross";
        case StatusAction::Quoting: return "Quoting";
        case StatusAction::Cross: return "Cross";
        case StatusAction::Rotation: return "Rotation";
        case StatusAction::NewPriceIndication: return "New Price Indication";
        case StatusAction::Trading: return "Trading";
        case StatusAction::Halt: return "Halt";
        case StatusAction::Pause: return "Pause";
        case StatusAction::Suspend: return "Suspend";
        case StatusAction::PreClose: return "Pre Close";
        case StatusAction::Close: return "Close";
        case StatusAction::PostClose: return "Post Close";
        case StatusAction::SsrChange: return "Ssr Change";
        case StatusAction::NotAvailableForTrading: return "Not Available For Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StatusAction value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v2
