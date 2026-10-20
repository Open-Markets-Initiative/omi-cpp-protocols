#include "TradingSessionSubId.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

std::string_view to_string(TradingSessionSubId value) {
    switch (value) {
        case TradingSessionSubId::Pause: return "Pause";
        case TradingSessionSubId::Close: return "Close";
        case TradingSessionSubId::Open: return "Open";
        case TradingSessionSubId::PreClose: return "Pre Close";
        case TradingSessionSubId::UnknownOrInvalid: return "Unknown Or Invalid";
        case TradingSessionSubId::PreOpen: return "Pre Open";
        case TradingSessionSubId::FinalClosingCall: return "Final Closing Call";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingSessionSubId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
