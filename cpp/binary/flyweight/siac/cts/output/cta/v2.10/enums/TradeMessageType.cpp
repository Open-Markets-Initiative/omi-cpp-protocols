#include "TradeMessageType.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(TradeMessageType value) {
    switch (value) {
        case TradeMessageType::AuctionStatusMessage: return "Auction Status Message";
        case TradeMessageType::TradeCorrectionMessage: return "Trade Correction Message";
        case TradeMessageType::FractionalTradeCorrectionMessage: return "Fractional Trade Correction Message";
        case TradeMessageType::LongTradeMessage: return "Long Trade Message";
        case TradeMessageType::FractionalLongTradeMessage: return "Fractional Long Trade Message";
        case TradeMessageType::TradingStatusMessage: return "Trading Status Message";
        case TradeMessageType::ShortTradeMessage: return "Short Trade Message";
        case TradeMessageType::FractionalShortTradeMessage: return "Fractional Short Trade Message";
        case TradeMessageType::TradeCancelErrorMessage: return "Trade Cancel Error Message";
        case TradeMessageType::FractionalTradeCancelErrorMessage: return "Fractional Trade Cancel Error Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
