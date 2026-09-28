#include "TradingSessionId.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

std::string_view to_string(TradingSessionId value) {
    switch (value) {
        case TradingSessionId::RegularTradingSession: return "Regular Trading Session";
        case TradingSessionId::NonRegularTradingSession: return "Non Regular Trading Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingSessionId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
