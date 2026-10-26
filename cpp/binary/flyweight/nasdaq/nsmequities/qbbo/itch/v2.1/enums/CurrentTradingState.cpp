#include "CurrentTradingState.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(CurrentTradingState value) {
    switch (value) {
        case CurrentTradingState::HaltedPaused: return "Halted Paused";
        case CurrentTradingState::QuotationOnly: return "Quotation Only";
        case CurrentTradingState::Paused: return "Paused";
        case CurrentTradingState::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CurrentTradingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
