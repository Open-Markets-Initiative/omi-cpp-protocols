#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/StockSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/BuyShares.hpp"
#include "../types/SellShares.hpp"
#include "../types/IndicativePrice.hpp"
#include "../types/AuctionOnlyPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// Auction Update messages are used to disseminate Cboe price and size information during auctions for Cboe listed securities and for Cboe Market Close (CMC) crosses.
struct AuctionUpdateMessage {

    TimeOffset time_offset;
    StockSymbol stock_symbol;
    AuctionType auction_type;
    ReferencePrice reference_price;
    BuyShares buy_shares;
    SellShares sell_shares;
    IndicativePrice indicative_price;
    AuctionOnlyPrice auction_only_price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x95;

    // parse method
    static AuctionUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionUpdateMessage*>(buffer);
    }

    // parse method const
    static const AuctionUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AuctionUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AuctionUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
