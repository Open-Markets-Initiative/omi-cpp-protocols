#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/ParticipantTimestamp.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbolLong.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/SecurityStatusIndicator.hpp"
#include "../types/BidPriceLowerLimitPriceBand.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/OfferPriceUpperLimitPriceBand.hpp"
#include "../types/OfferSizeLong.hpp"
#include "../types/RetailInterestIndicator.hpp"
#include "../types/SettlementCondition.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FinraMarketMakerId.hpp"
#include "../types/FinraBboIndicator.hpp"
#include "../structs/AdfTimestamp.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/SipGeneratedMessageIdentifier.hpp"
#include "../types/LuldIndicator.hpp"
#include "../types/NationalBboLuldIndicator.hpp"
#include "../types/NationalBboIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

// The Long Quote message is used to report quote data for a Cta eligible Equity, Local Issue or Bonds.
struct LongQuoteMessage {

    ParticipantId participant_id;
    ParticipantTimestamp participant_timestamp;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbolLong security_symbol_long;
    InstrumentType instrument_type;
    QuoteCondition quote_condition;
    SecurityStatusIndicator security_status_indicator;
    BidPriceLowerLimitPriceBand bid_price_lower_limit_price_band;
    BidSizeLong bid_size_long;
    OfferPriceUpperLimitPriceBand offer_price_upper_limit_price_band;
    OfferSizeLong offer_size_long;
    RetailInterestIndicator retail_interest_indicator;
    SettlementCondition settlement_condition;
    MarketCondition market_condition;
    FinraMarketMakerId finra_market_maker_id;
    FinraBboIndicator finra_bbo_indicator;
    AdfTimestamp adf_timestamp;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    SipGeneratedMessageIdentifier sip_generated_message_identifier;
    LuldIndicator luld_indicator;
    NationalBboLuldIndicator national_bbo_luld_indicator;
    NationalBboIndicator national_bbo_indicator;

    // parse method
    static LongQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<LongQuoteMessage*>(buffer);
    }

    // parse method const
    static const LongQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongQuoteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
