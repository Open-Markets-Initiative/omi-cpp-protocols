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
#include "../structs/ConsolidatedData.hpp"
#include "../structs/ParticipantData.hpp"
#include "../structs/SaleConditions.hpp"
#include "../structs/Timestamp1.hpp"
#include "../structs/Timestamp2.hpp"

namespace siac::cts::output::cta::v2_9 {

class TradeMessagePayloadVisitor;

// The Trade Cancel/Error message is used cancel or error Cta eligible securities, Local Issues
// or Bond information.
class TradeCancelErrorMessage : public TradeMessagePayload {
  public:
    // The code that selects this message
    static constexpr TradeMessagePayloadCode message_type = TradeMessageType::TradeCancelErrorMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 149;

    TradeCancelErrorMessage() = default;
    TradeCancelErrorMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const SaleConditions& sale_conditions, Decimal trade_price, std::uint32_t trade_volume, std::uint8_t sellers_sale_days, StopStockIndicator stop_stock_indicator, TradeThroughExemptIndicator trade_through_exempt_indicator, TradeReportingFacilityId trade_reporting_facility_id, std::int64_t original_participant_reference_number, const Timestamp2& timestamp_2, CancelErrorAction cancel_error_action, ShortSaleRestrictionIndicator short_sale_restriction_indicator, PrimaryListingMarketParticipantId primary_listing_market_participant_id, FinancialStatusIndicator financial_status_indicator, const ConsolidatedData& consolidated_data, const ParticipantData& participant_data);

    // Participant Id: Participant or Processor that generated the message
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

    // Transaction Id: The Transaction Id will be populated by CQS and is Reserved for Internal
    // Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: Participant Reference Number is a pass-thru of the inbound
    // Participant Reference number assigned to a transaction
    std::int64_t participant_reference_number() const;
    void set_participant_reference_number(std::int64_t value);

    // Security Symbol: Contains the security symbol
    const std::string& security_symbol() const;
    std::string& security_symbol();
    void set_security_symbol(const std::string& value);

    // Instrument Type: Identifies the instrument type relevant to the trade
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Sale Conditions: Sale Conditions
    const SaleConditions& sale_conditions() const;
    SaleConditions& sale_conditions();
    void set_sale_conditions(const SaleConditions& value);

    // Trade Price: The Trade Price is the monetary value of an individual share of security at
    // the time of the trade
    Decimal trade_price() const;
    void set_trade_price(Decimal value);

    // Trade Volume: Contains the total number of shares traded in a single transaction for an
    // individual security
    std::uint32_t trade_volume() const;
    void set_trade_volume(std::uint32_t value);

    // Sellers Sale Days: Specifies the number of days that may elapse before delivery of the
    // security
    std::uint8_t sellers_sale_days() const;
    void set_sellers_sale_days(std::uint8_t value);

    // Stop Stock Indicator: The transaction that constituted the trade-through was the
    // execution by a trading center of an order for which, at the time of receipt of the
    // order, the trading center had guaranteed an execution at no worse than a specified price
    StopStockIndicator stop_stock_indicator() const;
    void set_stop_stock_indicator(StopStockIndicator value);

    // Trade Through Exempt Indicator: Denotes whether or not a trade is exempt (Rule 611) and
    // when used jointly with certain Sale Conditions, will more fully describe the
    // characteristics of a particular trade
    TradeThroughExemptIndicator trade_through_exempt_indicator() const;
    void set_trade_through_exempt_indicator(TradeThroughExemptIndicator value);

    // Trade Reporting Facility Id: Identifies the Participant with whom a Trade Reporting
    // Facility has been formed
    TradeReportingFacilityId trade_reporting_facility_id() const;
    void set_trade_reporting_facility_id(TradeReportingFacilityId value);

    // Original Participant Reference Number: Contains the Participant Reference Number of
    // transaction to be corrected, cancelled or error
    std::int64_t original_participant_reference_number() const;
    void set_original_participant_reference_number(std::int64_t value);

    // Timestamp 2: Timestamp 2
    const Timestamp2& timestamp_2() const;
    Timestamp2& timestamp_2();
    void set_timestamp_2(const Timestamp2& value);

    // Cancel Error Action: Denotes whether the referenced transaction is to be cancelled or
    // error
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

    // Financial Status Indicator: Identifies the financial status of the security.
    FinancialStatusIndicator financial_status_indicator() const;
    void set_financial_status_indicator(FinancialStatusIndicator value);

    // Consolidated Data: Consolidated Data
    const ConsolidatedData& consolidated_data() const;
    ConsolidatedData& consolidated_data();
    void set_consolidated_data(const ConsolidatedData& value);

    // Participant Data: Participant Data
    const ParticipantData& participant_data() const;
    ParticipantData& participant_data();
    void set_participant_data(const ParticipantData& value);

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

    bool operator==(const TradeCancelErrorMessage& other) const;
    bool operator!=(const TradeCancelErrorMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    SaleConditions sale_conditions_{};
    Decimal trade_price_{ 0, -6 };
    std::uint32_t trade_volume_{};
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
    ConsolidatedData consolidated_data_{};
    ParticipantData participant_data_{};
};

} // namespace siac::cts::output::cta::v2_9
