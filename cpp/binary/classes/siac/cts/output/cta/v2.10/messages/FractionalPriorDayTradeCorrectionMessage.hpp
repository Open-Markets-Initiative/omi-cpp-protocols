#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/TradeReportingFacilityId.hpp"
#include "../messages/PriorDayMessagePayload.hpp"
#include "../structs/FractionalPriorDayCorrectedTrade.hpp"
#include "../structs/FractionalPriorDayOriginalTrade.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_10 {

class PriorDayMessagePayloadVisitor;

// Prior Day messages are used to report CTA eligible Equity, Local Issue or Bond trades,
// corrections, cancels or errors for transactions that occurred earlier than the current
// trading day and had not been reported
class FractionalPriorDayTradeCorrectionMessage : public PriorDayMessagePayload {
  public:
    // The code that selects this message
    static constexpr PriorDayMessagePayloadCode message_type = PriorDayMessageType::FractionalPriorDayTradeCorrectionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 99;

    FractionalPriorDayTradeCorrectionMessage() = default;
    FractionalPriorDayTradeCorrectionMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, const FractionalPriorDayCorrectedTrade& fractional_prior_day_corrected_trade, TradeReportingFacilityId trade_reporting_facility_id, const FractionalPriorDayOriginalTrade& fractional_prior_day_original_trade);

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

    // Fractional Prior Day Corrected Trade: Fractional Prior Day Corrected Trade
    const FractionalPriorDayCorrectedTrade& fractional_prior_day_corrected_trade() const;
    FractionalPriorDayCorrectedTrade& fractional_prior_day_corrected_trade();
    void set_fractional_prior_day_corrected_trade(const FractionalPriorDayCorrectedTrade& value);

    // Trade Reporting Facility Id: Identifies the Participant with whom a Trade Reporting
    // Facility has been formed
    TradeReportingFacilityId trade_reporting_facility_id() const;
    void set_trade_reporting_facility_id(TradeReportingFacilityId value);

    // Fractional Prior Day Original Trade: Fractional Prior Day Original Trade
    const FractionalPriorDayOriginalTrade& fractional_prior_day_original_trade() const;
    FractionalPriorDayOriginalTrade& fractional_prior_day_original_trade();
    void set_fractional_prior_day_original_trade(const FractionalPriorDayOriginalTrade& value);

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

    bool operator==(const FractionalPriorDayTradeCorrectionMessage& other) const;
    bool operator!=(const FractionalPriorDayTradeCorrectionMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    FractionalPriorDayCorrectedTrade fractional_prior_day_corrected_trade_{};
    TradeReportingFacilityId trade_reporting_facility_id_{};
    FractionalPriorDayOriginalTrade fractional_prior_day_original_trade_{};
};

} // namespace siac::cts::output::cta::v2_10
