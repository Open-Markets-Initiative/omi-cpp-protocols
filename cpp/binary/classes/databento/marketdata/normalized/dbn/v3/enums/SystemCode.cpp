#include "SystemCode.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

std::string_view to_string(SystemCode value) {
    switch (value) {
        case SystemCode::Heartbeat: return "Heartbeat";
        case SystemCode::SubscriptionAck: return "Subscription Ack";
        case SystemCode::SlowReaderWarning: return "Slow Reader Warning";
        case SystemCode::ReplayCompleted: return "Replay Completed";
        case SystemCode::EndOfInterval: return "End Of Interval";
        case SystemCode::UnsubscribeAck: return "Unsubscribe Ack";
        case SystemCode::Unset: return "Unset";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SystemCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v3
