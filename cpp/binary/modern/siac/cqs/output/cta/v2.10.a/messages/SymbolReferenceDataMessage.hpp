#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/PriorSecuritySymbol.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/PrimaryListingMarketPreviousClosingPrice.hpp"
#include "../types/ConsolidatedClosingPrice.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/Reserved.hpp"
#include "../types/LuldTier.hpp"
#include "../types/LuldLeverageRatio.hpp"
#include "../types/Test.hpp"
#include "../types/Ipo.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/HaltReason.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/SecondReserved.hpp"
#include "../types/ThirdReserved.hpp"
#include "../types/Reserved128.hpp"

namespace siac::cqs::output::cta::v2_10_a {

#pragma pack(push, 1)

// Symbol Reference Data Message
struct SymbolReferenceDataMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
    PriorSecuritySymbol prior_security_symbol;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    PrimaryListingMarketPreviousClosingPrice primary_listing_market_previous_closing_price;
    ConsolidatedClosingPrice consolidated_closing_price;
    RoundLotSize round_lot_size;
    Reserved reserved;
    LuldTier luld_tier;
    LuldLeverageRatio luld_leverage_ratio;
    Test test;
    Ipo ipo;
    FinancialStatusIndicator financial_status_indicator;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    HaltReason halt_reason;
    InstrumentType instrument_type;
    SecondReserved second_reserved;
    ThirdReserved third_reserved;
    Reserved128 reserved_128;

    // parse method
    static SymbolReferenceDataMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolReferenceDataMessage*>(buffer);
    }

    // parse method const
    static const SymbolReferenceDataMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolReferenceDataMessage*>(buffer);
    }
};

#pragma pack(pop)
}
