#include "TradingState.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

std::string_view to_string(TradingState value) {
    switch (value) {
        case TradingState::HaltedOrPaused: return "Halted Or Paused";
        case TradingState::HaltedOrPausedOnNasdaq: return "Halted Or Paused On Nasdaq";
        case TradingState::QuotationOnlyPeriod: return "Quotation Only Period";
        case TradingState::QuotationOnlyPeriodOnNasdaq: return "Quotation Only Period On Nasdaq";
        case TradingState::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
