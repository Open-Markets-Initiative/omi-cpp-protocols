#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/BidPriceShort.hpp"
#include "../types/BidSizeShort.hpp"
#include "../types/BidPriorityCustomerSizeShort.hpp"
#include "../types/BidCondition.hpp"
#include "../types/OfferPriceShort.hpp"
#include "../types/OfferSizeShort.hpp"
#include "../types/OfferPriorityCustomerSizeShort.hpp"
#include "../types/OfferCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// This is the message format that will be used in the real-time feed and refresh service to disseminate both sides of the MIAX Simple Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size.
struct SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage {

    Nanoseconds nanoseconds;
    ProductId product_id;
    BidPriceShort bid_price_short;
    BidSizeShort bid_size_short;
    BidPriorityCustomerSizeShort bid_priority_customer_size_short;
    BidCondition bid_condition;
    OfferPriceShort offer_price_short;
    OfferSizeShort offer_size_short;
    OfferPriorityCustomerSizeShort offer_priority_customer_size_short;
    OfferCondition offer_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'd';

    // parse method
    static SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage*>(buffer);
    }

    // parse method const
    static const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
