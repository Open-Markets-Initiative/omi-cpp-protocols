#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/AuctionCollarReferencePrice.hpp"
#include "../types/AuctionCollarUpperThresholdPrice.hpp"
#include "../types/AuctionCollarLowerThresholdPrice.hpp"
#include "../types/NumberOfExtensions.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/Reserved62.hpp"

namespace siac::cqs::output::cta::v2_10_a {

#pragma pack(push, 1)

// Used when a Participant in a CTA eligible security, Local Issue or Bonds reports requires Auction Information
struct AuctionStatusMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    InstrumentType instrument_type;
    AuctionCollarReferencePrice auction_collar_reference_price;
    AuctionCollarUpperThresholdPrice auction_collar_upper_threshold_price;
    AuctionCollarLowerThresholdPrice auction_collar_lower_threshold_price;
    NumberOfExtensions number_of_extensions;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    Reserved62 reserved_62;

    // parse method
    static AuctionStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AuctionStatusMessage*>(buffer);
    }

    // parse method const
    static const AuctionStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AuctionStatusMessage*>(buffer);
    }
};

#pragma pack(pop)
}
