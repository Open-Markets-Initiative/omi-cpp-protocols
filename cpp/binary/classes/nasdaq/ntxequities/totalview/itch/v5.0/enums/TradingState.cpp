#include "TradingState.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(TradingState value) {
    switch (value) {
        case TradingState::Halted: return "Halted";
        case TradingState::Paused: return "Paused";
        case TradingState::QuotationOnly: return "Quotation Only";
        case TradingState::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
