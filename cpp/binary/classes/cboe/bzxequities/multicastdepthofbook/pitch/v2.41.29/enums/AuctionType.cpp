#include "AuctionType.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::OpeningAuction: return "Opening Auction";
        case AuctionType::ClosingAuction: return "Closing Auction";
        case AuctionType::HaltAuction: return "Halt Auction";
        case AuctionType::IpoAuction: return "Ipo Auction";
        case AuctionType::CboeMarketClose: return "Cboe Market Close";
        case AuctionType::VolatilityAuction: return "Volatility Auction";
        case AuctionType::PeriodicAuction: return "Periodic Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
