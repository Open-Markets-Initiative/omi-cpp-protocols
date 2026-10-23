#include "TradingStatus.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::Active: return "Active";
        case TradingStatus::Halt: return "Halt";
        case TradingStatus::RegularTradingStartOfTradeReporting: return "Regular Trading Start Of Trade Reporting";
        case TradingStatus::OpeningFirstAuctionCall: return "Opening First Auction Call";
        case TradingStatus::PostClose: return "Post Close";
        case TradingStatus::MarketCloseSystemShutdown: return "Market Close System Shutdown";
        case TradingStatus::ClosingAuctionCall: return "Closing Auction Call";
        case TradingStatus::AespAuctionCall: return "Aesp Auction Call";
        case TradingStatus::ResumeAuctionCall: return "Resume Auction Call";
        case TradingStatus::Pause: return "Pause";
        case TradingStatus::PreMandatory: return "Pre Mandatory";
        case TradingStatus::Mandatory: return "Mandatory";
        case TradingStatus::PostMandatory: return "Post Mandatory";
        case TradingStatus::EdspAuctionCall: return "Edsp Auction Call";
        case TradingStatus::PeriodicAuctionCall: return "Periodic Auction Call";
        case TradingStatus::EndTradeReporting: return "End Trade Reporting";
        case TradingStatus::NoActiveSession: return "No Active Session";
        case TradingStatus::EndOfPostClose: return "End Of Post Close";
        case TradingStatus::ClosingPriceCrossing: return "Closing Price Crossing";
        case TradingStatus::ScheduledLevel1OnlyAuction: return "Scheduled Level 1 Only Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::millennium::level2::mitch::v11_9
