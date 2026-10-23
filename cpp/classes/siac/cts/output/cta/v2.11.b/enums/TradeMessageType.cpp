#include "TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(TradeMessageType value) {
    switch (value) {
        case TradeMessageType::AuctionStatus: return "Auction Status";
        case TradeMessageType::TradeCorrection: return "Trade Correction";
        case TradeMessageType::FractionalTradeCorrection: return "Fractional Trade Correction";
        case TradeMessageType::LongTrade: return "Long Trade";
        case TradeMessageType::FractionalLongTrade: return "Fractional Long Trade";
        case TradeMessageType::TradingStatus: return "Trading Status";
        case TradeMessageType::ShortTrade: return "Short Trade";
        case TradeMessageType::FractionalShortTrade: return "Fractional Short Trade";
        case TradeMessageType::TradeCancelError: return "Trade Cancel Error";
        case TradeMessageType::FractionalTradeCancelError: return "Fractional Trade Cancel Error";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
