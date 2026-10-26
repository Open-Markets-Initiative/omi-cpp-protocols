#pragma once

#include "../types/ParticipantId.hpp"
#include "../structs/Timestamp1.hpp"
#include "../types/MessageId.hpp"
#include "../types/TransactionId.hpp"
#include "../types/ParticipantReferenceNumber.hpp"
#include "../types/SecuritySymbol.hpp"
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
#include "../structs/Timestamp2.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/SipGeneratedMessageIdentifier.hpp"
#include "../types/LimitUpLimitDownLuldIndicator.hpp"
#include "../types/NationalBboLuldIndicator.hpp"
#include "../types/NationalBboIndicator.hpp"

namespace siac::cqs::output::cta::v2_10_a {

#pragma pack(push, 1)

// Reports quote data for a CTA eligible Equity, Local Issue or Bonds, including trading suspensions, price indications and trading range indications
struct LongQuoteMessage {

    ParticipantId participant_id;
    Timestamp1 timestamp_1;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbol security_symbol;
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
    Timestamp2 timestamp_2;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    SipGeneratedMessageIdentifier sip_generated_message_identifier;
    LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator;
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
