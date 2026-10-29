#include "AuctionStatus.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(AuctionStatus value) {
    switch (value) {
        case AuctionStatus::Usual: return "Usual";
        case AuctionStatus::LegalWidthQuoteDoesNotExist: return "Legal Width Quote Does Not Exist";
        case AuctionStatus::MarketMakerQuoteIsNotReceived: return "Market Maker Quote Is Not Received";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
