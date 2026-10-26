#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/TimeStamp.hpp"
#include "../types/Stock.hpp"
#include "../types/SecurityClass.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidSize.hpp"
#include "../types/BestOfferPrice.hpp"
#include "../types/BestOfferSize.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

#pragma pack(push, 1)

// BBO products will broadcast a real-time update every time that the exchange's best bid and offer quote is updated during the trading day.
struct BboQuotationMessage {

    TrackingNumber tracking_number;
    TimeStamp time_stamp;
    Stock stock;
    SecurityClass security_class;
    BestBidPrice best_bid_price;
    BestBidSize best_bid_size;
    BestOfferPrice best_offer_price;
    BestOfferSize best_offer_size;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Q';

    // parse method
    static BboQuotationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BboQuotationMessage*>(buffer);
    }

    // parse method const
    static const BboQuotationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BboQuotationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const BboQuotationMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const BboQuotationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
