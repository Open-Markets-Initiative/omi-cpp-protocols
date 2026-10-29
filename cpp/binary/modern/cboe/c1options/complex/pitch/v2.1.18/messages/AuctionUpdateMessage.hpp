#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/ComplexInstrumentId8.hpp"
#include "../types/AuctionOpeningType.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/BuyContracts.hpp"
#include "../types/SellContracts.hpp"
#include "../types/IndicativePrice.hpp"
#include "../types/AuctionOnlyPrice.hpp"
#include "../types/OpeningCondition.hpp"
#include "../types/CompositeMarketBidPrice.hpp"
#include "../types/CompositeMarketOfferPrice.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// Options Auction Update messages are used to disseminate price and size information during the Opening and Re-Opening (halt) process for complex instruments.
struct AuctionUpdateMessage {

    TimeOffset time_offset;
    ComplexInstrumentId8 complex_instrument_id_8;
    AuctionOpeningType auction_opening_type;
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
