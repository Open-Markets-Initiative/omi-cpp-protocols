#include "SymbolState.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(SymbolState value) {
    switch (value) {
        case SymbolState::Closed: return "Closed";
        case SymbolState::PreOpen: return "Pre Open";
        case SymbolState::OpeningAuction: return "Opening Auction";
        case SymbolState::ContinuousTrading: return "Continuous Trading";
        case SymbolState::ScheduledIntradayAuction: return "Scheduled Intraday Auction";
        case SymbolState::ClosingAuction: return "Closing Auction";
        case SymbolState::PostTrade: return "Post Trade";
        case SymbolState::Halted: return "Halted";
        case SymbolState::AuctionPeriod: return "Auction Period";
        case SymbolState::TradingAtClosingPrice: return "Trading At Closing Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SymbolState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
