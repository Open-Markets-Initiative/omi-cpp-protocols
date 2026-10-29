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
#include "../structs/AdfTimestamp.hpp"
#include "../structs/NationalBestBidLongAppendage.hpp"
#include "../structs/NationalBestBidShortAppendage.hpp"
#include "../structs/NationalBestOfferLongAppendage.hpp"
#include "../structs/NationalBestOfferShortAppendage.hpp"
#include "../structs/ParticipantTimestamp.hpp"

namespace siac::cqs::output::cta::v1_91 {

class QuoteMessagePayloadVisitor;

// The Long Quote message is used to report quote data for a Cta eligible Equity, Local Issue
// or Bonds.
class LongQuoteMessage : public QuoteMessagePayload {
  public:
    // The code that selects this message
    static constexpr QuoteMessagePayloadCode message_type = QuoteMessageType::LongQuoteMessage;

    LongQuoteMessage() = default;
    LongQuoteMessage(ParticipantId participant_id, const ParticipantTimestamp& participant_timestamp, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol_long, InstrumentType instrument_type, QuoteCondition quote_condition, SecurityStatusIndicator security_status_indicator, Decimal bid_price_lower_limit_price_band, std::uint32_t bid_size_long, Decimal offer_price_upper_limit_price_band, std::uint32_t offer_size_long, RetailInterestIndicator retail_interest_indicator, SettlementCondition settlement_condition, MarketCondition market_condition, const std::string& finra_market_maker_id, FinraBboIndicator finra_bbo_indicator, const AdfTimestamp& adf_timestamp, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, SipGeneratedMessageIdentifier sip_generated_message_identifier, char luld_indicator, NationalBboLuldIndicator national_bbo_luld_indicator, NationalBboIndicator national_bbo_indicator, const std::optional<NationalBestBidLongAppendage>& national_best_bid_long_appendage, const std::optional<NationalBestOfferLongAppendage>& national_best_offer_long_appendage, const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage, const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage);

    // Participant Id: Participant or Processor that generated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Participant Timestamp: Participant Timestamp
    const ParticipantTimestamp& participant_timestamp() const;
    ParticipantTimestamp& participant_timestamp();
    void set_participant_timestamp(const ParticipantTimestamp& value);

    // Message Id: The Message ID identifies the individual message within the block beginning
    // with number one
    std::uint8_t message_id() const;
    void set_message_id(std::uint8_t value);

    // Transaction Id: The Transaction Id will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol Long: Contains the security symbol
    const std::string& security_symbol_long() const;
    std::string& security_symbol_long();
    void set_security_symbol_long(const std::string& value);

    // Instrument Type: Identifies the instrument type relevant to the quote
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Quote Condition: Denotes a particular condition applicable to the quote.
    QuoteCondition quote_condition() const;
    void set_quote_condition(QuoteCondition value);

    // Security Status Indicator: The Security Status Indicator field is used to report trading
    // suspensions in a security, price indications, trading range indications, LULD Price
    // Bands and Market Wide Circuit Breaker activity
    SecurityStatusIndicator security_status_indicator() const;
    void set_security_status_indicator(SecurityStatusIndicator value);

    // Bid Price Lower Limit Price Band: Represents the lower price band value for a security.
    Decimal bid_price_lower_limit_price_band() const;
    void set_bid_price_lower_limit_price_band(Decimal value);

    // Bid Size Long: The Bid Size identifies the number of round-lots, for a security
    std::uint32_t bid_size_long() const;
    void set_bid_size_long(std::uint32_t value);

    // Offer Price Upper Limit Price Band: represents the upper price band value for a
    // security.
    Decimal offer_price_upper_limit_price_band() const;
    void set_offer_price_upper_limit_price_band(Decimal value);

    // Offer Size Long: The Offer Size identifies the number of round-lots, for a security
    std::uint32_t offer_size_long() const;
    void set_offer_size_long(std::uint32_t value);

    // Retail Interest Indicator: When Retail Price Improvement (RPI) interest is priced better
    // than the Protected Best Bid or Offer (PBBO) by a minimum of $0.001, an indication of
    // interest on the Bid, Offer, or both the Bid and Offer will identify that interest will
    // be eligible to interact with incoming Retail Order interest.
    RetailInterestIndicator retail_interest_indicator() const;
    void set_retail_interest_indicator(RetailInterestIndicator value);

    // Settlement Condition: Identifies the settlement condition for a security
    SettlementCondition settlement_condition() const;
    void set_settlement_condition(SettlementCondition value);

    // Market Condition: Identifies the market condition of a quote for a security.
    MarketCondition market_condition() const;
    void set_market_condition(MarketCondition value);

    // Finra Market Maker Id: Contains the FINRA Market Maker ID of the quoting participant on
    // FINRA's Alternative Display Facility (ADF) or the FINRA ADF Identifier
    const std::string& finra_market_maker_id() const;
    std::string& finra_market_maker_id();
    void set_finra_market_maker_id(const std::string& value);

    // Finra Bbo Indicator: For FINRA ADF, represents the FINRA BBO state of the FINRA ADF
    // quote
    FinraBboIndicator finra_bbo_indicator() const;
    void set_finra_bbo_indicator(FinraBboIndicator value);

    // Adf Timestamp: Adf Timestamp
    const AdfTimestamp& adf_timestamp() const;
    AdfTimestamp& adf_timestamp();
    void set_adf_timestamp(const AdfTimestamp& value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market for a
    // security
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security.
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Sip Generated Message Identifier: Identifies CQS as the originator of a message
    SipGeneratedMessageIdentifier sip_generated_message_identifier() const;
    void set_sip_generated_message_identifier(SipGeneratedMessageIdentifier value);

    // Luld Indicator: Indicates the affect the Quote has on the Limit Up-Limit Down Price Band
    // range.
    char luld_indicator() const;
    void set_luld_indicator(char value);

    // National Bbo Luld Indicator: Indicates the affect that the Limit Up-Limit Down Price
    // Band changes have on the National Best Bid and National Best Offer
    NationalBboLuldIndicator national_bbo_luld_indicator() const;
    void set_national_bbo_luld_indicator(NationalBboLuldIndicator value);

    // National Bbo Indicator: Indicates the affect the new quote has on the National BBO.
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

    // National Best Bid Short Appendage: National Best Bid Short Appendage
    const std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage() const;
    std::optional<NationalBestBidShortAppendage>& national_best_bid_short_appendage();
    void set_national_best_bid_short_appendage(const std::optional<NationalBestBidShortAppendage>& value);

    // National Best Offer Short Appendage: National Best Offer Short Appendage
    const std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage() const;
    std::optional<NationalBestOfferShortAppendage>& national_best_offer_short_appendage();
    void set_national_best_offer_short_appendage(const std::optional<NationalBestOfferShortAppendage>& value);

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
    ParticipantTimestamp participant_timestamp_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_long_{};
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
    AdfTimestamp adf_timestamp_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    SipGeneratedMessageIdentifier sip_generated_message_identifier_{};
    char luld_indicator_{};
    NationalBboLuldIndicator national_bbo_luld_indicator_{};
    NationalBboIndicator national_bbo_indicator_{};
    std::optional<NationalBestBidLongAppendage> national_best_bid_long_appendage_{};
    std::optional<NationalBestOfferLongAppendage> national_best_offer_long_appendage_{};
    std::optional<NationalBestBidShortAppendage> national_best_bid_short_appendage_{};
    std::optional<NationalBestOfferShortAppendage> national_best_offer_short_appendage_{};
};

} // namespace siac::cqs::output::cta::v1_91
