#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/IndexSymbol.hpp"
#include "../types/BidIndexValue.hpp"
#include "../types/OfferIndexValue.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

// The Bid and Offer Index message contains the index Bid and Offer index values
struct BidAndOfferIndexMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    IndexSymbol index_symbol;
    BidIndexValue bid_index_value;
    OfferIndexValue offer_index_value;

    // parse method
    static BidAndOfferIndexMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BidAndOfferIndexMessage*>(buffer);
    }

    // parse method const
    static const BidAndOfferIndexMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BidAndOfferIndexMessage*>(buffer);
    }
};

#pragma pack(pop)
}
