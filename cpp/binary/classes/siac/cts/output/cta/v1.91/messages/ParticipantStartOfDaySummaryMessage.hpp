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
#include "../messages/SummaryMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v1_91 {

class SummaryMessagePayloadVisitor;

// The Participant Start of Day Summary messages are transmitted shortly after the Multicast
// Line ‘Start of Day’ message
class ParticipantStartOfDaySummaryMessage : public SummaryMessagePayload {
  public:
    // The code that selects this message
    static constexpr SummaryMessagePayloadCode message_type = SummaryMessageType::ParticipantStartOfDaySummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 47;

    ParticipantStartOfDaySummaryMessage() = default;
    ParticipantStartOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, char summary_participant_id, std::uint32_t previous_close_price_date, Decimal previous_close_price);

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

    // Summary Participant Id: Identifies the Participant whose summary information is provided
    char summary_participant_id() const;
    void set_summary_participant_id(char value);

    // Previous Close Price Date: Represents the date the security last traded
    std::uint32_t previous_close_price_date() const;
    void set_previous_close_price_date(std::uint32_t value);

    // Previous Close Price: The Previous Close Price represents the last qualifying price paid
    // for a security during the trading day
    Decimal previous_close_price() const;
    void set_previous_close_price(Decimal value);

    // SummaryMessagePayload
    SummaryMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SummaryMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<SummaryMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SummaryMessagePayload& other) const override;

    bool operator==(const ParticipantStartOfDaySummaryMessage& other) const;
    bool operator!=(const ParticipantStartOfDaySummaryMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    char summary_participant_id_{};
    std::uint32_t previous_close_price_date_{};
    Decimal previous_close_price_{ 0, -6 };
};

} // namespace siac::cts::output::cta::v1_91
