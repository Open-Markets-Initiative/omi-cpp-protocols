#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/StockSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/PriceBinary8.hpp"
#include "../types/Shares.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Auction Summary message
struct AuctionSummaryMessage {

    TimeOffset time_offset;
    StockSymbol stock_symbol;
    AuctionType auction_type;
    PriceBinary8 price_binary_8;
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
