#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// ‘S’ = Start ‘U’ = Auction Update ‘E’ = End of Auction
enum class AuctionEvent : char {
    Start = 'S',         // Start
    AuctionUpdate = 'U', // Auction Update
    EndOfAuction = 'E',  // End Of Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionEvent value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
