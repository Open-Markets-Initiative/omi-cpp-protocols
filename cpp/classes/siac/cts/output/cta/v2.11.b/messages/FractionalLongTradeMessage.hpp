#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ConsolidatedHighLowLastIndicator.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/HeldTradeIndicator.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/ParticipantOpenHighLowLastIndicator.hpp"
#include "../enums/PrimaryListingMarketParticipantId.hpp"
#include "../enums/ShortSaleRestrictionIndicator.hpp"
#include "../enums/StopStockIndicator.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../enums/TradeThroughExemptIndicator.hpp"
#include "../messages/TradeMessagePayload.hpp"
#include "../structs/SaleCondition4.hpp"
#include "../structs/Timestamp1.hpp"
#include "../structs/Timestamp2.hpp"

namespace siac::cts::output::cta::v2_11_b {

class TradeMessagePayloadVisitor;

// Used to report trade information for CTA eligible Equity, Local Issue or Bonds. Volume is
// represented as a fractional value
class FractionalLongTradeMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::FractionalLongTrade;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 72;

    FractionalLongTradeMessage() = default;
    FractionalLongTradeMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const SaleCondition4& sale_condition_4, Decimal trade_price, std::uint64_t fractional_trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, TradeReportingFacilityId trade_reporting_facility_id, const Timestamp2& timestamp_2, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, HeldTradeIndicator held_trade_indicator, ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator, ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator);

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

    // Instrument Type: Identifies the instrument type relevant to the trade
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Sale Condition 4: Sale Condition 4
    const SaleCondition4& sale_condition_4() const;
    SaleCondition4& sale_condition_4();
    void set_sale_condition_4(const SaleCondition4& value);

    // Trade Price: Represents the monetary value of an individual share of security at the
    // time of the trade. Has implied 6 decimal places
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Fractional Trade Volume: Contains the total number of shares which traded in a single
    // transaction for an individual security. Has implied 6 decimal places
    std::uint64_t fractional_trade_volume() const;
    void set_fractional_trade_volume(std::uint64_t value);

    // Sellers Sale Days: Specifies the number of days that may elapse before delivery of the
    // security. Allowed values 2 through 60 days
    std::uint8_t sellers_sale_days() const;
    void set_sellers_sale_days(std::uint8_t value);

    // Stop Stock Indicator: Identifies whether the transaction constituted a stopped order
    StopStockIndicator stop_stock_indicator() const;
    void set_stop_stock_indicator(StopStockIndicator value);

    // Trade Through Exempt Indicator: Denotes whether or not a trade is exempt (Rule 611)
    TradeThroughExemptIndicator trade_through_exempt_indicator() const;
    void set_trade_through_exempt_indicator(TradeThroughExemptIndicator value);

    // Trade Reporting Facility Id: Identifies the Participant with whom a Trade Reporting
    // Facility (TRF) has been formed. Space-filled
    TradeReportingFacilityId trade_reporting_facility_id() const;
    void set_trade_reporting_facility_id(TradeReportingFacilityId value);

    // Timestamp 2: Timestamp 2
    const Timestamp2& timestamp_2() const;
    Timestamp2& timestamp_2();
    void set_timestamp_2(const Timestamp2& value);

    // Short Sale Restriction Indicator: Identifies whether or not a Short Sale Restriction is
    // in effect for a security
    ShortSaleRestrictionIndicator short_sale_restriction_indicator() const;
    void set_short_sale_restriction_indicator(ShortSaleRestrictionIndicator value);

    // Primary Listing Market Participant Id: Identifies the Primary Listing Market of the
    // security symbol
    PrimaryListingMarketParticipantId primary_listing_market_participant_id() const;
    void set_primary_listing_market_participant_id(PrimaryListingMarketParticipantId value);

    // Financial Status Indicator: Identifies the financial status of the security
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Held Trade Indicator: Reflects whether a held trade qualifies for the Participant or
    // Consolidated Last Price at the time it is disseminated
    HeldTradeIndicator held_trade_indicator() const;
    void set_held_trade_indicator(HeldTradeIndicator value);

    // Consolidated High Low Last Indicator: Identifies the Consolidated High/Low/Last Price
    // applicable to the trade
    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator() const;
    void set_consolidated_high_low_last_indicator(ConsolidatedHighLowLastIndicator value);

    // Participant Open High Low Last Indicator: Identifies the Participant Open/High/Low/Last
    // applicable to the transaction
    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator() const;
    void set_participant_open_high_low_last_indicator(ParticipantOpenHighLowLastIndicator value);

    // TradeMessagePayload
    TradeMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(TradeMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<TradeMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const TradeMessagePayload& other) const override;

    bool operator==(const FractionalLongTradeMessage& other) const;
    bool operator!=(const FractionalLongTradeMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    SaleCondition4 sale_condition_4_{};
    Decimal trade_price_{ 0, -6 };
    std::uint64_t fractional_trade_volume_{};
    std::uint8_t sellers_sale_days_{};
    StopStockIndicator stop_stock_indicator_{};
    TradeThroughExemptIndicator trade_through_exempt_indicator_{};
    TradeReportingFacilityId trade_reporting_facility_id_{};
    Timestamp2 timestamp_2_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    HeldTradeIndicator held_trade_indicator_{};
    ConsolidatedHighLowLastIndicator consolidated_high_low_last_indicator_{};
    ParticipantOpenHighLowLastIndicator participant_open_high_low_last_indicator_{};
};

} // namespace siac::cts::output::cta::v2_11_b
