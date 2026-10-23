#include "StatisticType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(StatisticType value) {
    switch (value) {
        case StatisticType::IndicativeAuctionUncrossingData: return "Indicative Auction Uncrossing Data";
        case StatisticType::OfficialOpeningPrice: return "Official Opening Price";
        case StatisticType::OfficialClosingPrice: return "Official Closing Price";
        case StatisticType::TradeHighOnBook: return "Trade High On Book";
        case StatisticType::TradeLowOnBook: return "Trade Low On Book";
        case StatisticType::TradeHighAllTrades: return "Trade High All Trades";
        case StatisticType::TradeLowAllTrades: return "Trade Low All Trades";
        case StatisticType::FiftyTwoWeekTradeHighAllTrades: return "Fifty Two Week Trade High All Trades";
        case StatisticType::FiftyTwoWeekTradeLowAllTrades: return "Fifty Two Week Trade Low All Trades";
        case StatisticType::BestClosingBid: return "Best Closing Bid";
        case StatisticType::BestClosingAsk: return "Best Closing Ask";
        case StatisticType::StaticReferencePrice: return "Static Reference Price";
        case StatisticType::DynamicReferencePrice: return "Dynamic Reference Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StatisticType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
