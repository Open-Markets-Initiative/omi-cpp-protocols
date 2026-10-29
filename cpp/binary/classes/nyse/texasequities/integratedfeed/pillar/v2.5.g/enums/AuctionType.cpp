#include "AuctionType.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::EarlyOpeningAuction: return "Early Opening Auction";
        case AuctionType::CoreOpeningAuction: return "Core Opening Auction";
        case AuctionType::ReopeningAuctionHaltResume: return "Reopening Auction Halt Resume";
        case AuctionType::ClosingAuction: return "Closing Auction";
        case AuctionType::ExtremeClosingImbalance: return "Extreme Closing Imbalance";
        case AuctionType::SignificantClosingImbalance: return "Significant Closing Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
