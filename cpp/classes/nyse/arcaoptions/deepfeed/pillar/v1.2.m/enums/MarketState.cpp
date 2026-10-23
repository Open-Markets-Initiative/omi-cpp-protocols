#include "MarketState.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(MarketState value) {
    switch (value) {
        case MarketState::Preopening: return "Preopening";
        case MarketState::EarlySession: return "Early Session";
        case MarketState::CoreSession: return "Core Session";
        case MarketState::LateSessionNonNyseOnly: return "Late Session Non Nyse Only";
        case MarketState::Closed: return "Closed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
