#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/MbboPriceLong.hpp"
#include "../types/MbboSizeLong.hpp"
#include "../types/MbboPriorityCustomerSizeLong.hpp"
#include "../types/MbboCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate MIAX Simple Top of Market for options with high premiums or large aggregate MIAX Best Bid or Offer (MBBO) size. "b" = Simple Top of Market on Bid side (wide).
struct SimpleTopOfMarketBestBidOrOfferWideBidMessage {

    Nanoseconds nanoseconds;
    ProductId product_id;
    MbboPriceLong mbbo_price_long;
    MbboSizeLong mbbo_size_long;
    MbboPriorityCustomerSizeLong mbbo_priority_customer_size_long;
    MbboCondition mbbo_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'b';

    // parse method
    static SimpleTopOfMarketBestBidOrOfferWideBidMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleTopOfMarketBestBidOrOfferWideBidMessage*>(buffer);
    }

    // parse method const
    static const SimpleTopOfMarketBestBidOrOfferWideBidMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleTopOfMarketBestBidOrOfferWideBidMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SimpleTopOfMarketBestBidOrOfferWideBidMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SimpleTopOfMarketBestBidOrOfferWideBidMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
