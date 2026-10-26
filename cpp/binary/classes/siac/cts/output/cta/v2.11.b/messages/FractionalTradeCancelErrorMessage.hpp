#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/CancelErrorAction.hpp"
#include "../enums/FinancialStatusIndicator.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
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

// Used to cancel or error CTA eligible securities, Local Issues or Bond information. Volume is
// represented as a fractional value
class FractionalTradeCancelErrorMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::FractionalTradeCancelError;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 161;

    FractionalTradeCancelErrorMessage() = default;
    FractionalTradeCancelErrorMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const SaleCondition4& sale_condition_4, Decimal trade_price, Decimal fractional_trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, TradeReportingFacilityId trade_reporting_facility_id, std::int64_t original_participant_reference_number, const Timestamp2& timestamp_2, CancelErrorAction cancel_error_action, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, std::uint32_t consolidated_previous_close_price_date, char consolidated_last_participant_id, Decimal consolidated_last_price, Decimal consolidated_high_price, Decimal consolidated_low_price, Decimal consolidated_fractional_total_volume, char consolidated_tick, std::uint32_t participant_previous_close_price_date, Decimal participant_last_price, Decimal participant_high_price, Decimal participant_low_price, Decimal participant_open_price, Decimal participant_fractional_total_volume, char participant_tick);

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
    Decimal fractional_trade_volume() const;
    void set_fractional_trade_volume(Decimal value);

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

    // Original Participant Reference Number: Contains the Participant Reference Number of
    // transaction to be corrected, cancelled or errored
    std::int64_t original_participant_reference_number() const;
    void set_original_participant_reference_number(std::int64_t value);

    // Timestamp 2: Timestamp 2
    const Timestamp2& timestamp_2() const;
    Timestamp2& timestamp_2();
    void set_timestamp_2(const Timestamp2& value);

    // Cancel Error Action: Denotes whether the referenced transaction is to be cancelled or
    // errored
    CancelErrorAction cancel_error_action() const;
    void set_cancel_error_action(CancelErrorAction value);

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

    // Consolidated Previous Close Price Date: Consolidated date the security last traded.
    // Represented in seconds since Epoch
    std::uint32_t consolidated_previous_close_price_date() const;
    void set_consolidated_previous_close_price_date(std::uint32_t value);

    // Consolidated Last Participant Id: Consolidated last participant ID
    char consolidated_last_participant_id() const;
    void set_consolidated_last_participant_id(char value);

    // Consolidated Last Price: Consolidated last price. Has implied 6 decimal places
    Decimal consolidated_last_price() const;
    void set_consolidated_last_price(Decimal value);

    // Consolidated High Price: Consolidated highest price paid during the trading day. Has
    // implied 6 decimal places
    Decimal consolidated_high_price() const;
    void set_consolidated_high_price(Decimal value);

    // Consolidated Low Price: Consolidated lowest price paid during the trading day. Has
    // implied 6 decimal places
    Decimal consolidated_low_price() const;
    void set_consolidated_low_price(Decimal value);

    // Consolidated Fractional Total Volume: Consolidated total volume of shares traded. Has
    // implied 6 decimal places
    Decimal consolidated_fractional_total_volume() const;
    void set_consolidated_fractional_total_volume(Decimal value);

    // Consolidated Tick: Consolidated tick direction
    char consolidated_tick() const;
    void set_consolidated_tick(char value);

    // Participant Previous Close Price Date: Participant date the security last traded.
    // Represented in seconds since Epoch
    std::uint32_t participant_previous_close_price_date() const;
    void set_participant_previous_close_price_date(std::uint32_t value);

    // Participant Last Price: Participant last price. Has implied 6 decimal places
    Decimal participant_last_price() const;
    void set_participant_last_price(Decimal value);

    // Participant High Price: Participant highest price paid during the trading day. Has
    // implied 6 decimal places
    Decimal participant_high_price() const;
    void set_participant_high_price(Decimal value);

    // Participant Low Price: Participant lowest price paid during the trading day. Has implied
    // 6 decimal places
    Decimal participant_low_price() const;
    void set_participant_low_price(Decimal value);

    // Participant Open Price: Participant first qualifying price paid during the trading day.
    // Has implied 6 decimal places
    Decimal participant_open_price() const;
    void set_participant_open_price(Decimal value);

    // Participant Fractional Total Volume: Participant total volume of shares traded. Has
    // implied 6 decimal places
    Decimal participant_fractional_total_volume() const;
    void set_participant_fractional_total_volume(Decimal value);

    // Participant Tick: Participant tick direction
    char participant_tick() const;
    void set_participant_tick(char value);

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

    bool operator==(const FractionalTradeCancelErrorMessage& other) const;
    bool operator!=(const FractionalTradeCancelErrorMessage& other) const;

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
    Decimal fractional_trade_volume_{ 0, -6 };
    std::uint8_t sellers_sale_days_{};
    StopStockIndicator stop_stock_indicator_{};
    TradeThroughExemptIndicator trade_through_exempt_indicator_{};
    TradeReportingFacilityId trade_reporting_facility_id_{};
    std::int64_t original_participant_reference_number_{};
    Timestamp2 timestamp_2_{};
    CancelErrorAction cancel_error_action_{};
    ShortSaleRestrictionIndicator short_sale_restriction_indicator_{};
    PrimaryListingMarketParticipantId primary_listing_market_participant_id_{};
    FinancialStatusIndicator financial_status_indicator_{};
    std::uint32_t consolidated_previous_close_price_date_{};
    char consolidated_last_participant_id_{};
    Decimal consolidated_last_price_{ 0, -6 };
    Decimal consolidated_high_price_{ 0, -6 };
    Decimal consolidated_low_price_{ 0, -6 };
    Decimal consolidated_fractional_total_volume_{ 0, -6 };
    char consolidated_tick_{};
    std::uint32_t participant_previous_close_price_date_{};
    Decimal participant_last_price_{ 0, -6 };
    Decimal participant_high_price_{ 0, -6 };
    Decimal participant_low_price_{ 0, -6 };
    Decimal participant_open_price_{ 0, -6 };
    Decimal participant_fractional_total_volume_{ 0, -6 };
    char participant_tick_{};
};

} // namespace siac::cts::output::cta::v2_11_b
