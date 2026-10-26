#include "AuctionType.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::EarlyOpeningAuctionNonNyseOnly: return "Early Opening Auction Non Nyse Only";
        case AuctionType::CoreOpeningAuction: return "Core Opening Auction";
        case AuctionType::ReopeningAuctionHaltResume: return "Reopening Auction Halt Resume";
        case AuctionType::ClosingAuction: return "Closing Auction";
        case AuctionType::ExtremeClosingImbalance: return "Extreme Closing Imbalance";
        case AuctionType::RegulatoryClosingImbalance: return "Regulatory Closing Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
