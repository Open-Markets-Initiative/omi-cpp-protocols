#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/BuyShares.hpp"
#include "../types/SellShares.hpp"
#include "../types/IndicativePrice.hpp"
#include "../types/AuctionOnlyPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// On the BYX Exchange, Auction Update messages will be sent out at a randomized time between the start of an auction period and the end of the auction period minus 1 millisecond to inform participants that a Periodic Auction is taking place
struct AuctionUpdateMessage {

    TimeOffset time_offset;
    SymbolLong symbol_long;
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
