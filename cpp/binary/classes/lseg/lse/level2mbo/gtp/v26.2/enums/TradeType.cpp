#include "TradeType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(TradeType value) {
    switch (value) {
        case TradeType::RegularOrContinuousTrade: return "Regular Or Continuous Trade";
        case TradeType::AuctionTradeBulk: return "Auction Trade Bulk";
        case TradeType::AuctionTradeIndividual: return "Auction Trade Individual";
        case TradeType::OnBookTradeCancellation: return "On Book Trade Cancellation";
        case TradeType::TradeCorrection: return "Trade Correction";
        case TradeType::RfqTrade: return "Rfq Trade";
        case TradeType::RfqTradeCancellation: return "Rfq Trade Cancellation";
        case TradeType::RfqTradeCorrection: return "Rfq Trade Correction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
