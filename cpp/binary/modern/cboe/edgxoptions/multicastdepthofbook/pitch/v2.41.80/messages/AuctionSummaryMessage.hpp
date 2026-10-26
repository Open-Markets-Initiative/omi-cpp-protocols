#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/StockSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/PriceLong.hpp"
#include "../types/SharesContracts.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// Auction Summary messages are used to disseminate the results of an auction of a Cboe listed security on BZX, the results of an Opening or Re-Opening of any options series on C1, and for Periodic Auctions on BYX. Auction Summary messages are also used in support of Opening and Re-Openings on the Cboe Options Exchange, including those for both GTH and RTH sessions. These messages indicate the price and size executed in such an Opening or Re-Opening.
struct AuctionSummaryMessage {

    TimeOffset time_offset;
    StockSymbol stock_symbol;
    AuctionType auction_type;
    PriceLong price_long;
    SharesContracts shares_contracts;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x96;

    // parse method
    static AuctionSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionSummaryMessage*>(buffer);
    }

    // parse method const
    static const AuctionSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
