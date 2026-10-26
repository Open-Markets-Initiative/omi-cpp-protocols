#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/BidPriceLong.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/BidPriorityCustomerSizeLong.hpp"
#include "../types/BidCondition.hpp"
#include "../types/OfferPriceLong.hpp"
#include "../types/OfferSizeLong.hpp"
#include "../types/OfferPriorityCustomerSizeLong.hpp"
#include "../types/OfferCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// This is the message format that will be used in the real-time feed and refresh service to disseminate both sides of the MIAX Simple Top of Market for options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) sizes.
struct SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage {

    Nanoseconds nanoseconds;
    ProductId product_id;
    BidPriceLong bid_price_long;
    BidSizeLong bid_size_long;
    BidPriorityCustomerSizeLong bid_priority_customer_size_long;
    BidCondition bid_condition;
    OfferPriceLong offer_price_long;
    OfferSizeLong offer_size_long;
    OfferPriorityCustomerSizeLong offer_priority_customer_size_long;
    OfferCondition offer_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage*>(buffer);
    }

    // parse method const
    static const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
