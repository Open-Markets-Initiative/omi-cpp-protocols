#include "AuctionType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(AuctionType value) {
    switch (value) {
        case AuctionType::EarlyOpeningAuction: return "Early Opening Auction";
        case AuctionType::CoreOpeningAuction: return "Core Opening Auction";
        case AuctionType::ReopeningAuctionHaltResume: return "Reopening Auction Halt Resume";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
