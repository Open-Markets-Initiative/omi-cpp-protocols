#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../messages/PriorDayMessagePayload.hpp"
#include "../structs/CorrectedPriorDayTradeDateAndTime.hpp"
#include "../structs/OriginalPriorDayTradeDateAndTime.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class PriorDayMessagePayloadVisitor;

// Used to correct a transaction originally reported on a trading day earlier than the current
// trading day. To be descoped when Fractional Trade Volume publication is activated
class PriorDayTradeCorrectionMessage : public PriorDayMessagePayload {
  public:
    // The code that selects this message
    static constexpr PriorDayMessagePayloadCode message_type = PriorDayMessageType::PriorDayTradeCorrection;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 91;

    PriorDayTradeCorrectionMessage() = default;
    PriorDayTradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const std::string& corrected_sale_condition, Decimal corrected_trade_price, std::uint32_t corrected_trade_volume, std::uint8_t corrected_sellers_sale_days, char corrected_stop_stock_indicator, char corrected_trade_through_exempt_indicator, char corrected_short_sale_restriction_indicator, const CorrectedPriorDayTradeDateAndTime& corrected_prior_day_trade_date_and_time, TradeReportingFacilityId trade_reporting_facility_id, const std::string& original_sale_condition, Decimal original_trade_price, std::uint32_t original_trade_volume, std::uint8_t original_sellers_sale_days, char original_stop_stock_indicator, char original_trade_through_exempt_indicator, char original_short_sale_restriction_indicator, const OriginalPriorDayTradeDateAndTime& original_prior_day_trade_date_and_time);

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

    // Corrected Sale Condition: Corrected sale condition associated with a trade
    const std::string& corrected_sale_condition() const;
    std::string& corrected_sale_condition();
    void set_corrected_sale_condition(const std::string& value);

    // Corrected Trade Price: Corrected monetary value of an individual share of security. Has
    // implied 6 decimal places
    Decimal corrected_trade_price() const;
    void set_corrected_trade_price(Decimal value);

    // Corrected Trade Volume: Corrected total number of shares which traded in a single
    // transaction for an individual security
    std::uint32_t corrected_trade_volume() const;
    void set_corrected_trade_volume(std::uint32_t value);

    // Corrected Sellers Sale Days: Corrected number of days that may elapse before delivery of
    // the security
    std::uint8_t corrected_sellers_sale_days() const;
    void set_corrected_sellers_sale_days(std::uint8_t value);

    // Corrected Stop Stock Indicator: Corrected stop stock indicator
    char corrected_stop_stock_indicator() const;
    void set_corrected_stop_stock_indicator(char value);

    // Corrected Trade Through Exempt Indicator: Corrected trade through exempt indicator
    char corrected_trade_through_exempt_indicator() const;
    void set_corrected_trade_through_exempt_indicator(char value);

    // Corrected Short Sale Restriction Indicator: Corrected short sale restriction indicator
    char corrected_short_sale_restriction_indicator() const;
    void set_corrected_short_sale_restriction_indicator(char value);

    // Corrected Prior Day Trade Date and Time: The corrected prior day trade date and time
    const CorrectedPriorDayTradeDateAndTime& corrected_prior_day_trade_date_and_time() const;
    CorrectedPriorDayTradeDateAndTime& corrected_prior_day_trade_date_and_time();
    void set_corrected_prior_day_trade_date_and_time(const CorrectedPriorDayTradeDateAndTime& value);

    // Trade Reporting Facility Id: Identifies the Participant with whom a Trade Reporting
    // Facility (TRF) has been formed. Space-filled
    TradeReportingFacilityId trade_reporting_facility_id() const;
    void set_trade_reporting_facility_id(TradeReportingFacilityId value);

    // Original Sale Condition: Original sale condition associated with a trade
    const std::string& original_sale_condition() const;
    std::string& original_sale_condition();
    void set_original_sale_condition(const std::string& value);

    // Original Trade Price: Original monetary value of an individual share of security. Has
    // implied 6 decimal places
    Decimal original_trade_price() const;
    void set_original_trade_price(Decimal value);

    // Original Trade Volume: Original total number of shares which traded in a single
    // transaction for an individual security
    std::uint32_t original_trade_volume() const;
    void set_original_trade_volume(std::uint32_t value);

    // Original Sellers Sale Days: Original number of days that may elapse before delivery of
    // the security
    std::uint8_t original_sellers_sale_days() const;
    void set_original_sellers_sale_days(std::uint8_t value);

    // Original Stop Stock Indicator: Original stop stock indicator
    char original_stop_stock_indicator() const;
    void set_original_stop_stock_indicator(char value);

    // Original Trade Through Exempt Indicator: Original trade through exempt indicator
    char original_trade_through_exempt_indicator() const;
    void set_original_trade_through_exempt_indicator(char value);

    // Original Short Sale Restriction Indicator: Original short sale restriction indicator
    char original_short_sale_restriction_indicator() const;
    void set_original_short_sale_restriction_indicator(char value);

    // Original Prior Day Trade Date and Time: The original prior day trade date and time
    const OriginalPriorDayTradeDateAndTime& original_prior_day_trade_date_and_time() const;
    OriginalPriorDayTradeDateAndTime& original_prior_day_trade_date_and_time();
    void set_original_prior_day_trade_date_and_time(const OriginalPriorDayTradeDateAndTime& value);

    // PriorDayMessagePayload
    PriorDayMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(PriorDayMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<PriorDayMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const PriorDayMessagePayload& other) const override;

    bool operator==(const PriorDayTradeCorrectionMessage& other) const;
    bool operator!=(const PriorDayTradeCorrectionMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    std::string corrected_sale_condition_{};
    Decimal corrected_trade_price_{ 0, -6 };
    std::uint32_t corrected_trade_volume_{};
    std::uint8_t corrected_sellers_sale_days_{};
    char corrected_stop_stock_indicator_{};
    char corrected_trade_through_exempt_indicator_{};
    char corrected_short_sale_restriction_indicator_{};
    CorrectedPriorDayTradeDateAndTime corrected_prior_day_trade_date_and_time_{};
    TradeReportingFacilityId trade_reporting_facility_id_{};
    std::string original_sale_condition_{};
    Decimal original_trade_price_{ 0, -6 };
    std::uint32_t original_trade_volume_{};
    std::uint8_t original_sellers_sale_days_{};
    char original_stop_stock_indicator_{};
    char original_trade_through_exempt_indicator_{};
    char original_short_sale_restriction_indicator_{};
    OriginalPriorDayTradeDateAndTime original_prior_day_trade_date_and_time_{};
};

} // namespace siac::cts::output::cta::v2_11_b
