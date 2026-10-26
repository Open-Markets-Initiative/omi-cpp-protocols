#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/Ipo.hpp"
#include "../enums/LuldTier.hpp"
#include "../enums/MinimumPriceIncrementIndicator.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/Test.hpp"
#include "../messages/AdministrativeMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class AdministrativeMessagePayloadVisitor;

// Symbol Reference Data message
class SymbolReferenceDataMessage : public AdministrativeMessagePayload {
  public:
    // The code that selects this message
    static constexpr AdministrativeMessagePayloadCode message_type = AdministrativeMessageType::SymbolReferenceData;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 205;

    SymbolReferenceDataMessage() = default;
    SymbolReferenceDataMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, const std::string& prior_security_symbol, PrimaryListingMarketParticipantId primary_listing_market_participant_id, Decimal primary_listing_market_previous_closing_price, Decimal consolidated_closing_price, std::uint16_t round_lot_size, MinimumPriceIncrementIndicator minimum_price_increment_indicator, LuldTier luld_tier, Decimal luld_leverage_ratio, Test test, Ipo ipo, FinancialStatusIndicator financial_status_indicator, ShortSaleRestrictionIndicator short_sale_restriction_indicator, HaltReason halt_reason, InstrumentType instrument_type, char reserved, char second_reserved, const std::string& reserved_128);

    // Participant Id: Identifies the Participant or Processor that initiated the message
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

    // Transaction Id: Identifies the transaction
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Contains the Participant Reference Number
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol: Identifies the Security Symbol. Left justified, space-filled
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Prior Security Symbol: Contains the prior Security Symbol
    const std::string& prior_security_symbol() const;
    std::string& prior_security_symbol();
    void set_prior_security_symbol(const std::string& value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Primary Listing Market Previous Closing Price: Represents the previous closing price for
    // the primary listing market. Has implied 6 decimal places
    Decimal primary_listing_market_previous_closing_price() const;
    void set_primary_listing_market_previous_closing_price(Decimal value);

    // Consolidated Closing Price: Represents the consolidated closing price. Has implied 6
    // decimal places
    Decimal consolidated_closing_price() const;
    void set_consolidated_closing_price(Decimal value);

    // Round Lot Size: Round-lot size for a symbol can consist of 1, 10, 40 or 100 shares
    std::uint16_t round_lot_size() const;
    void set_round_lot_size(std::uint16_t value);

    // Minimum Price Increment Indicator: Identifies the applicable tick size for a symbol
    MinimumPriceIncrementIndicator minimum_price_increment_indicator() const;
    void set_minimum_price_increment_indicator(MinimumPriceIncrementIndicator value);

    // Luld Tier: Identifies the Limit Up Limit Down tier of the security symbol
    LuldTier luld_tier() const;
    void set_luld_tier(LuldTier value);

    // Luld Leverage Ratio: Represents the Leverage ratio associated with the LULD Tier of the
    // security symbol. Has implied 6 decimal places
    Decimal luld_leverage_ratio() const;
    void set_luld_leverage_ratio(Decimal value);

    // Test: Identifies whether the security symbol is a test symbol
    Test test() const;
    void set_test(Test value);

    // Ipo: Identifies whether the security symbol is an IPO
    Ipo ipo() const;
    void set_ipo(Ipo value);

    // Financial Status Indicator: Identifies the financial status of the security
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect for a security
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Halt Reason: Denotes the reason for the Trading Halt
    HaltReason halt_reason() const;
    void set_halt_reason(HaltReason value);

    // Instrument Type: Identifies the instrument type relevant to the trade
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Reserved: Space-filled. Field is reserved for future use
    char reserved() const;
    void set_reserved(char value);

    // Second Reserved: Space-filled. Field is reserved for future use
    char second_reserved() const;
    void set_second_reserved(char value);

    // Reserved 128: Space-filled. Field is reserved for future use
    const std::string& reserved_128() const;
    std::string& reserved_128();
    void set_reserved_128(const std::string& value);

    // AdministrativeMessagePayload
    AdministrativeMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(AdministrativeMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<AdministrativeMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const AdministrativeMessagePayload& other) const override;

    bool operator==(const SymbolReferenceDataMessage& other) const;
    bool operator!=(const SymbolReferenceDataMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    std::string prior_security_symbol_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    Decimal primary_listing_market_previous_closing_price_{ 0, -6 };
    Decimal consolidated_closing_price_{ 0, -6 };
    std::uint16_t round_lot_size_{};
    MinimumPriceIncrementIndicator minimum_price_increment_indicator_{};
    LuldTier luld_tier_{};
    Decimal luld_leverage_ratio_{ 0, -6 };
    Test test_{};
    Ipo ipo_{};
    FinancialStatusIndicator financial_status_indicator_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    HaltReason halt_reason_{};
    InstrumentType instrument_type_{};
    char reserved_{};
    char second_reserved_{};
    std::string reserved_128_{};
};

} // namespace siac::cts::output::cta::v2_11_b
