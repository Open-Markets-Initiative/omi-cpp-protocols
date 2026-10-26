#include "AuctionStatus.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(AuctionStatus value) {
    switch (value) {
        case AuctionStatus::WillRunAsUsual: return "Will Run As Usual";
        case AuctionStatus::AuctionWillNotRunBecauseLegalWidthQuoteDoesNotExist: return "Auction Will Not Run Because Legal Width Quote Does Not Exist";
        case AuctionStatus::AuctionWillNotRunBecauseMarketMakerQuoteIsNotReceived: return "Auction Will Not Run Because Market Maker Quote Is Not Received";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
