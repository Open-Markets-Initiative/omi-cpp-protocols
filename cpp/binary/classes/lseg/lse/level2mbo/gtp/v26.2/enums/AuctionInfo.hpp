#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Populated if the Statistic Type is 1.
enum class AuctionInfo : char {
    NotApplicable = '0',                // Not Applicable
    BuyImbalance = 'B',                 // Buy Imbalance
    NoImbalance = 'N',                  // No Imbalance
    InsufficientOrdersForAuction = 'O', // Insufficient Orders For Auction
    SellImbalance = 'S',                // Sell Imbalance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionInfo value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionInfo value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
