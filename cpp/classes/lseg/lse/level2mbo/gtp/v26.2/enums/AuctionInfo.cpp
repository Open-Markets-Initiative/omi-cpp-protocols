#include "AuctionInfo.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(AuctionInfo value) {
    switch (value) {
        case AuctionInfo::NotApplicable: return "Not Applicable";
        case AuctionInfo::BuyImbalance: return "Buy Imbalance";
        case AuctionInfo::NoImbalance: return "No Imbalance";
        case AuctionInfo::InsufficientOrdersForAuction: return "Insufficient Orders For Auction";
        case AuctionInfo::SellImbalance: return "Sell Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AuctionInfo value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
