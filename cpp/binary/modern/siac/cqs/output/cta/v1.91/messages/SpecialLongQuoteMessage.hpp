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
#include "../types/BidPriceLong.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/OfferPriceLong.hpp"
#include "../types/OfferSizeLong.hpp"
#include "../types/RetailInterestIndicator.hpp"
#include "../types/SettlementCondition.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FinraMarketMakerId.hpp"
#include "../types/FinraBestBidQuoteCondition.hpp"
#include "../types/FinraBestBidPrice.hpp"
#include "../types/FinraBestBidSize.hpp"
#include "../types/FinraBestBidMarketMakerId.hpp"
#include "../types/FinraBestOfferQuoteCondition.hpp"
#include "../types/FinraBestOfferPrice.hpp"
#include "../types/FinraBestOfferSize.hpp"
#include "../types/FinraBestOfferMarketMakerId.hpp"
#include "../structs/AdfTimestamp.hpp"
#include "../types/ShortSaleRestrictionIndicator.hpp"
#include "../types/PrimaryListingMarketParticipantId.hpp"
#include "../types/FinancialStatusIndicator.hpp"
#include "../types/SipGeneratedMessageIdentifier.hpp"
#include "../types/FinraBboLuldIndicator.hpp"
#include "../types/NationalBboLuldIndicator.hpp"
#include "../types/NationalBboIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

// The Special Quote (FINRA ADF) with FINRA BBO Information message is used only by FINRA to report the FINRA Best Bid and FINRA Best Offer for their Market Makers for Cta eligible Equity, Local Issue or Bond information Makers inclusive of changes to any existing FINRA BBO.
struct SpecialLongQuoteMessage {

    ParticipantId participant_id;
    ParticipantTimestamp participant_timestamp;
    MessageId message_id;
    TransactionId transaction_id;
    ParticipantReferenceNumber participant_reference_number;
    SecuritySymbolLong security_symbol_long;
    InstrumentType instrument_type;
    QuoteCondition quote_condition;
    SecurityStatusIndicator security_status_indicator;
    BidPriceLong bid_price_long;
    BidSizeLong bid_size_long;
    OfferPriceLong offer_price_long;
    OfferSizeLong offer_size_long;
    RetailInterestIndicator retail_interest_indicator;
    SettlementCondition settlement_condition;
    MarketCondition market_condition;
    FinraMarketMakerId finra_market_maker_id;
    FinraBestBidQuoteCondition finra_best_bid_quote_condition;
    FinraBestBidPrice finra_best_bid_price;
    FinraBestBidSize finra_best_bid_size;
    FinraBestBidMarketMakerId finra_best_bid_market_maker_id;
    FinraBestOfferQuoteCondition finra_best_offer_quote_condition;
    FinraBestOfferPrice finra_best_offer_price;
    FinraBestOfferSize finra_best_offer_size;
    FinraBestOfferMarketMakerId finra_best_offer_market_maker_id;
    AdfTimestamp adf_timestamp;
    ShortSaleRestrictionIndicator short_sale_restriction_indicator;
    PrimaryListingMarketParticipantId primary_listing_market_participant_id;
    FinancialStatusIndicator financial_status_indicator;
    SipGeneratedMessageIdentifier sip_generated_message_identifier;
    FinraBboLuldIndicator finra_bbo_luld_indicator;
    NationalBboLuldIndicator national_bbo_luld_indicator;
    NationalBboIndicator national_bbo_indicator;

    // parse method
    static SpecialLongQuoteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SpecialLongQuoteMessage*>(buffer);
    }

    // parse method const
    static const SpecialLongQuoteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SpecialLongQuoteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
