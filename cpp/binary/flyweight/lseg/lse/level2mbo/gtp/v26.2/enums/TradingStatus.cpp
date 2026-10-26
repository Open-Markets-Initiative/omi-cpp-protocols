#include "TradingStatus.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::Halt: return "Halt";
        case TradingStatus::HaltMatchingPartitionSuspended: return "Halt Matching Partition Suspended";
        case TradingStatus::HaltSystemSuspended: return "Halt System Suspended";
        case TradingStatus::RegularTradingStartTradeReporting: return "Regular Trading Start Trade Reporting";
        case TradingStatus::HaltRegulatory: return "Halt Regulatory";
        case TradingStatus::EndTradeReporting: return "End Trade Reporting";
        case TradingStatus::OpeningAuctionCall: return "Opening Auction Call";
        case TradingStatus::PostClose: return "Post Close";
        case TradingStatus::Closed: return "Closed";
        case TradingStatus::ClosingAuctionCall: return "Closing Auction Call";
        case TradingStatus::AespAuctionCall: return "Aesp Auction Call";
        case TradingStatus::ResumeAuction: return "Resume Auction";
        case TradingStatus::PreMandatory: return "Pre Mandatory";
        case TradingStatus::Mandatory: return "Mandatory";
        case TradingStatus::PostMandatory: return "Post Mandatory";
        case TradingStatus::EdspAuctionCall: return "Edsp Auction Call";
        case TradingStatus::PeriodicAuctionCall: return "Periodic Auction Call";
        case TradingStatus::Inactive: return "Inactive";
        case TradingStatus::Suspended: return "Suspended";
        case TradingStatus::NoActiveSession: return "No Active Session";
        case TradingStatus::EndOfPostClose: return "End Of Post Close";
        case TradingStatus::ClosingPriceCrossingSession: return "Closing Price Crossing Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
