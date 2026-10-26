#pragma once

#include "../types/MessageIndicator.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/Reserved1.hpp"
#include "../types/IndexValueDenominatorCode.hpp"
#include "../types/BidIndexValue.hpp"
#include "../types/OfferIndexValue.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

// Underlying value bid and offer message
struct UnderlyingValueBidAndOfferMessage {

    MessageIndicator message_indicator;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    Reserved1 reserved_1;
    IndexValueDenominatorCode index_value_denominator_code;
    BidIndexValue bid_index_value;
    OfferIndexValue offer_index_value;

    // parse method
    static UnderlyingValueBidAndOfferMessage* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingValueBidAndOfferMessage*>(buffer);
    }

    // parse method const
    static const UnderlyingValueBidAndOfferMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingValueBidAndOfferMessage*>(buffer);
    }
};

#pragma pack(pop)
}
