#include "AuctionType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::ClosingAuction: return "Closing Auction";
        case AuctionType::OpeningAuction: return "Opening Auction";
        case AuctionType::Aesp: return "Aesp";
        case AuctionType::Edsp: return "Edsp";
        case AuctionType::ResumeAuction: return "Resume Auction";
        case AuctionType::PeriodicAuction: return "Periodic Auction";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
