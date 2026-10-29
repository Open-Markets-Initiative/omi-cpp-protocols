#include "CurrentTradingState.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(CurrentTradingState value) {
    switch (value) {
        case CurrentTradingState::HaltInEffect: return "Halt In Effect";
        case CurrentTradingState::TradingResumed: return "Trading Resumed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CurrentTradingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
