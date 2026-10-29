#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/InitiatingParticipantId.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/ParticipantId.hpp"
#include "../enums/Tick.hpp"
#include "../messages/SummaryMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_10 {

class SummaryMessagePayloadVisitor;

// The Participant End of Day Summary messages are transmitted shortly before the ‘Goodnight’
// messages.
class ParticipantEndOfDaySummaryMessage : public SummaryMessagePayload {
  public:
    // The code that selects this message
    static constexpr SummaryMessagePayloadCode message_type = SummaryMessageType::ParticipantEndOfDaySummaryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 80;

    ParticipantEndOfDaySummaryMessage() = default;
    ParticipantEndOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, InitiatingParticipantId initiating_participant_id, std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, Decimal open_price, std::uint64_t total_volume, Tick tick);

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

    // Initiating Participant Id: Participant or Processor that generated the message
    InitiatingParticipantId initiating_participant_id() const;
    void set_initiating_participant_id(InitiatingParticipantId value);

    // Previous Close Price Date: Represents the date the security last traded
    std::uint32_t previous_close_price_date() const;
    void set_previous_close_price_date(std::uint32_t value);

    // Last Price: The Last Price represents the last price for that security either on a
    // Consolidated or an individual Participant basis at the time it is disseminated
    Decimal last_price() const;
    void set_last_price(Decimal value);

    // High Price: The High Price represents the highest price paid for a security during the
    // trading day
    Decimal high_price() const;
    void set_high_price(Decimal value);

    // Low Price: The Low Price represents the lowest price paid for a security during the
    // trading day
    Decimal low_price() const;
    void set_low_price(Decimal value);

    // Open Price: The Open Price represents the first qualifying price paid for a security
    // during the trading day.
    Decimal open_price() const;
    void set_open_price(Decimal value);

    // Total Volume: Contains Total Volume of shares traded in a security either on a
    // Consolidated or an individual Participant basis at the time it is disseminated
    std::uint64_t total_volume() const;
    void set_total_volume(std::uint64_t value);

    // Tick: Represents for a Participant the upward, downward or unchanged price movement in a
    // security's trades
    Tick tick() const;
    void set_tick(Tick value);

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

    bool operator==(const ParticipantEndOfDaySummaryMessage& other) const;
    bool operator!=(const ParticipantEndOfDaySummaryMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
    std::string security_symbol_{};
    InstrumentType instrument_type_{};
    InitiatingParticipantId initiating_participant_id_{};
    std::uint32_t previous_close_price_date_{};
    Decimal last_price_{ 0, -6 };
    Decimal high_price_{ 0, -6 };
    Decimal low_price_{ 0, -6 };
    Decimal open_price_{ 0, -6 };
    std::uint64_t total_volume_{};
    Tick tick_{};
};

} // namespace siac::cts::output::cta::v2_10
