#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/FinraBboIndicator.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/LimitUpLimitDownLuldIndicator.hpp"
#include "../enums/MarketCondition.hpp"
#include "../enums/NationalBboIndicator.hpp"
#include "../enums/NationalBboLuldIndicator.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/QuoteCondition.hpp"
#include "../enums/RetailInterestIndicator.hpp"
#include "../enums/SecurityStatusIndicator.hpp"
#include "../enums/SettlementCondition.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/SipGeneratedMessageIdentifier.hpp"
#include "../messages/QuoteMessagePayload.hpp"
#include "../structs/NationalBestBidAndOfferLongAppendage.hpp"
#include "../structs/NationalBestBidAndOfferShortAppendage.hpp"
#include "../structs/NationalBestBidLongAppendage.hpp"
#include "../structs/NationalBestBidShortAppendage.hpp"
#include "../structs/NationalBestOfferLongAppendage.hpp"
#include "../structs/NationalBestOfferShortAppendage.hpp"
#include "../structs/Timestamp1.hpp"
#include "../structs/Timestamp2.hpp"

namespace siac::cqs::output::cta::v2_10_a {

class QuoteMessagePayloadVisitor;

// Reports quote data for a CTA eligible Equity, Local Issue or Bonds, including trading
// suspensions, price indications and trading range indications
class LongQuoteMessage : public QuoteMessagePayload {
  public:
    // The code that selects this message
    static constexpr QuoteMessagePayloadCode message_type = QuoteMessageType::LongQuote;

    LongQuoteMessage() = default;
    LongQuoteMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, QuoteCondition quote_condition, SecurityStatusIndicator security_status_indicator, Decimal bid_price_lower_limit_price_band, std::uint32_t bid_size_long, Decimal offer_price_upper_limit_price_band, std::uint32_t offer_size_long, RetailInterestIndicator retail_interest_indicator, SettlementCondition settlement_condition, MarketCondition market_condition, const std::string& finra_market_maker_id, FinraBboIndicator finra_bbo_indicator, const Timestamp2& timestamp_2, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, SipGeneratedMessageIdentifier sip_generated_message_identifier, LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator, NationalBboLuldIndicator national_bbo_luld_indicator, NationalBboIndicator national_bbo_indicator, const std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage, const std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage, const std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage, const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage, const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage, const std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage);

    // Participant Id: Identifies the Participant or Processor that generated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Timestamp 1: Timestamp 1
    const Timestamp1& timestamp_1() const;
    Timestamp1& timestamp_1();
    void set_timestamp_1(const Timestamp1& value);

    // Message Id: The Message ID identifies the individual message within the block beginning
    // with number one
    std::uint8_t message_id() const;
    void set_message_id(std::uint8_t value);

    // Transaction Id: The Transaction ID will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol: Contains the security symbol. Left justified, space-filled
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Instrument Type: Identifies the instrument type relevant to the quote
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Quote Condition: Denotes a particular condition applicable to the quote used to
    // determine whether a quote qualifies for the Best Bid and Best Offer calculation
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Security Status Indicator: Reports trading suspensions, price indications, trading range
    // indications, LULD Price Bands and Market Wide Circuit Breaker activity
    SecurityStatusIndicator security_status_indicator() const;
    void set_security_status_indicator(SecurityStatusIndicator value);

    // Bid Price Lower Limit Price Band: Bid Price represents the highest price a prospective
    // buyer is prepared to pay; Lower Limit Price Band represents the lower price band value
    // when Security Status Indicator is Limit Up-Limit Down Price Band
    Decimal bid_price_lower_limit_price_band() const;
    void set_bid_price_lower_limit_price_band(Decimal value);

    // Bid Size Long: Identifies the number of shares for a symbol rounded down to the nearest
    // multiple of its Round Lot Size
    std::uint32_t bid_size_long() const;
    void set_bid_size_long(std::uint32_t value);

    // Offer Price Upper Limit Price Band: Offer Price represents the lowest price acceptable
    // to a prospective seller at a particular time for a security; Upper Limit Price Band
    // represents the upper price band value when Security Status Indicator is Limit Up-Limit
    // Down Price Band
    Decimal offer_price_upper_limit_price_band() const;
    void set_offer_price_upper_limit_price_band(Decimal value);

    // Offer Size Long: Identifies the number of shares for a symbol rounded down to the
    // nearest multiple of its Round Lot Size
    std::uint32_t offer_size_long() const;
    void set_offer_size_long(std::uint32_t value);

    // Retail Interest Indicator: Identifies Retail Price Improvement interest priced better
    // than the Protected Best Bid or Offer by a minimum of $0.001
    RetailInterestIndicator retail_interest_indicator() const;
    void set_retail_interest_indicator(RetailInterestIndicator value);

    // Settlement Condition: Identifies the settlement condition for a security
    SettlementCondition settlement_condition() const;
    void set_settlement_condition(SettlementCondition value);

    // Market Condition: Identifies the market condition of a quote for a security
    MarketCondition market_condition() const;
    void set_market_condition(MarketCondition value);

    // Finra Market Maker Id: Contains the FINRA Market Maker ID of the quoting participant on
    // FINRA's Alternative Display Facility or the FINRA ADF Identifier 'FNRA'
    const std::string& finra_market_maker_id() const;
    std::string& finra_market_maker_id();
    void set_finra_market_maker_id(const std::string& value);

    // Finra Bbo Indicator: For FINRA ADF, represents the FINRA BBO state of the FINRA ADF
    // quote
    FinraBboIndicator finra_bbo_indicator() const;
    void set_finra_bbo_indicator(FinraBboIndicator value);

    // Timestamp 2: Timestamp 2
    const Timestamp2& timestamp_2() const;
    Timestamp2& timestamp_2();
    void set_timestamp_2(const Timestamp2& value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market for a
    // security
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Sip Generated Message Identifier: Identifies CQS as the originator of a message
    SipGeneratedMessageIdentifier sip_generated_message_identifier() const;
    void set_sip_generated_message_identifier(SipGeneratedMessageIdentifier value);

    // Limit Up Limit Down Luld Indicator: Indicates the effect the Quote has on the Limit
    // Up-Limit Down Price Band range
    LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator() const;
    void set_limit_up_limit_down_luld_indicator(LimitUpLimitDownLuldIndicator value);

    // National Bbo Luld Indicator: Indicates the effect that the Limit Up-Limit Down Price
    // Band changes have on the National Best Bid and National Best Offer
    NationalBboLuldIndicator national_bbo_luld_indicator() const;
    void set_national_bbo_luld_indicator(NationalBboLuldIndicator value);

    // National Bbo Indicator: Indicates the effect the new quote has on the National BBO
    NationalBboIndicator national_bbo_indicator() const;
    void set_national_bbo_indicator(NationalBboIndicator value);

    // National Best Bid Long Appendage: National Best Bid Long Appendage
    const std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage() const;
    std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage();
    void set_national_best_bid_long_appendage(const std::optional<NationalBestBidLongAppendage>& value);

    // National Best Offer Long Appendage: National Best Offer Long Appendage
    const std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage() const;
    std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage();
    void set_national_best_offer_long_appendage(const std::optional<NationalBestOfferLongAppendage>& value);

    // National Best Bid And Offer Long Appendage: National Best Bid And Offer Long Appendage
    const std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage() const;
    std::optional<NationalBestBidAndOfferLongAppendage>& national_best_bid_and_offer_long_appendage();
    void set_national_best_bid_and_offer_long_appendage(const std::optional<NationalBestBidAndOfferLongAppendage>& value);

    // National Best Bid Short Appendage: National Best Bid Short Appendage
    const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage() const;
    std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage();
    void set_national_best_bid_short_appendage(const std::optional<NationalBestBidShortAppendage>& value);

    // National Best Offer Short Appendage: National Best Offer Short Appendage
    const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage() const;
    std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage();
    void set_national_best_offer_short_appendage(const std::optional<NationalBestOfferShortAppendage>& value);

    // National Best Bid And Offer Short Appendage: National Best Bid And Offer Short Appendage
    const std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage() const;
    std::optional<NationalBestBidAndOfferShortAppendage>& national_best_bid_and_offer_short_appendage();
    void set_national_best_bid_and_offer_short_appendage(const std::optional<NationalBestBidAndOfferShortAppendage>& value);

    // QuoteMessagePayload
    QuoteMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(QuoteMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<QuoteMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const QuoteMessagePayload& other) const override;

    bool operator==(const LongQuoteMessage& other) const;
    bool operator!=(const LongQuoteMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    QuoteCondition quote_condition_{};
    SecurityStatusIndicator security_status_indicator_{};
    Decimal bid_price_lower_limit_price_band_{ 0, -6 };
    std::uint32_t bid_size_long_{};
    Decimal offer_price_upper_limit_price_band_{ 0, -6 };
    std::uint32_t offer_size_long_{};
    RetailInterestIndicator retail_interest_indicator_{};
    SettlementCondition settlement_condition_{};
    MarketCondition market_condition_{};
    std::string finra_market_maker_id_{};
    FinraBboIndicator finra_bbo_indicator_{};
    Timestamp2 timestamp_2_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    SipGeneratedMessageIdentifier sip_generated_message_identifier_{};
    LimitUpLimitDownLuldIndicator limit_up_limit_down_luld_indicator_{};
    NationalBboLuldIndicator national_bbo_luld_indicator_{};
    NationalBboIndicator national_bbo_indicator_{};
    std::optional<NationalBestBidLongAppendage> national_best_bid_long_appendage_{};
    std::optional<NationalBestOfferLongAppendage> national_best_offer_long_appendage_{};
    std::optional<NationalBestBidAndOfferLongAppendage> national_best_bid_and_offer_long_appendage_{};
    std::optional<NationalBestBidShortAppendage> national_best_bid_short_appendage_{};
    std::optional<NationalBestOfferShortAppendage> national_best_offer_short_appendage_{};
    std::optional<NationalBestBidAndOfferShortAppendage> national_best_bid_and_offer_short_appendage_{};
};

} // namespace siac::cqs::output::cta::v2_10_a
