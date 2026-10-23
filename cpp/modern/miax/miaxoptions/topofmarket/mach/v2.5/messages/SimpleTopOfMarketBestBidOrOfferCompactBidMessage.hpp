#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/MbboPriceShort.hpp"
#include "../types/MbboSizeShort.hpp"
#include "../types/MbboPriorityCustomerSizeShort.hpp"
#include "../types/MbboCondition.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// This is the message format that will be used to disseminate each side of the MIAX Simple Top of Market for options with low premiums and small aggregate MIAX Best Bid or Offer (MBBO) size. "B" = Simple Top of Market on Bid side.
struct SimpleTopOfMarketBestBidOrOfferCompactBidMessage {

    Nanoseconds nanoseconds;
    ProductId product_id;
    MbboPriceShort mbbo_price_short;
    MbboSizeShort mbbo_size_short;
    MbboPriorityCustomerSizeShort mbbo_priority_customer_size_short;
    MbboCondition mbbo_condition;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'B';

    // parse method
    static SimpleTopOfMarketBestBidOrOfferCompactBidMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SimpleTopOfMarketBestBidOrOfferCompactBidMessage*>(buffer);
    }

    // parse method const
    static const SimpleTopOfMarketBestBidOrOfferCompactBidMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SimpleTopOfMarketBestBidOrOfferCompactBidMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SimpleTopOfMarketBestBidOrOfferCompactBidMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SimpleTopOfMarketBestBidOrOfferCompactBidMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
