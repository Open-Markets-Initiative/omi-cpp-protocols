#include "AuctionType.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::OpeningAuction: return "Opening Auction";
        case AuctionType::ClosingAuction: return "Closing Auction";
        case AuctionType::IpoAuction: return "Ipo Auction";
        case AuctionType::HaltAuction: return "Halt Auction";
        case AuctionType::VolatilityAuction: return "Volatility Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::tops::iextp::v1_56
