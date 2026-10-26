#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/ExpandedSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/BuyContracts.hpp"
#include "../types/SellContracts.hpp"
#include "../types/IndicativePrice.hpp"
#include "../types/AuctionOnlyPrice.hpp"
#include "../types/OpeningCondition.hpp"
#include "../types/CompositeMarketBidPrice.hpp"
#include "../types/CompositeMarketOfferPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// Options Only. Options Auction Update messages are used to disseminate price and size information and Composite Market bid and offer prices during Opening and Re-Opening (halt) auctions on the Cboe Options Exchange. Options Auction Update messages are sent every five seconds during an opening period provided that one of the field values has changed. When no values have changed, a message is sent once every 60 seconds. Refer to the Cboe Options Opening Process specification for more information.
struct OptionsAuctionUpdateMessage {

    TimeOffset time_offset;
    ExpandedSymbol expanded_symbol;
    AuctionType auction_type;
    ReferencePrice reference_price;
    BuyContracts buy_contracts;
    SellContracts sell_contracts;
    IndicativePrice indicative_price;
    AuctionOnlyPrice auction_only_price;
    OpeningCondition opening_condition;
    CompositeMarketBidPrice composite_market_bid_price;
    CompositeMarketOfferPrice composite_market_offer_price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0xD1;

    // parse method
    static OptionsAuctionUpdateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OptionsAuctionUpdateMessage*>(buffer);
    }

    // parse method const
    static const OptionsAuctionUpdateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OptionsAuctionUpdateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OptionsAuctionUpdateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OptionsAuctionUpdateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
