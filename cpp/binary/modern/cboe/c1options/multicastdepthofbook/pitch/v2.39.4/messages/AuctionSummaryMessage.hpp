#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/StockSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/LongPrice.hpp"
#include "../types/Shares.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// Auction Summary messages are used to disseminate the results of an auction of a Cboe listed security.
struct AuctionSummaryMessage {

    TimeOffset time_offset;
    StockSymbol stock_symbol;
    AuctionType auction_type;
    LongPrice long_price;
    Shares shares;

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
