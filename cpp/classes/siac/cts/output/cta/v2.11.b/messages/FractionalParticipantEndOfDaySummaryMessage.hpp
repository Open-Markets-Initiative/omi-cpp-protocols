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
#include "../enums/Tick.hpp"
#include "../messages/SummaryMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class SummaryMessagePayloadVisitor;

// Provides by security, the Participant Open, High, Low, Last, Volume and Tick information for
// CTA eligible securities, Local Issues and Bonds. Volume is represented as a fractional value
class FractionalParticipantEndOfDaySummaryMessage : public SummaryMessagePayload {
  public:
    // The code that selects this message
    static constexpr SummaryMessagePayloadCode message_type = SummaryMessageType::FractionalParticipantEndOfDaySummary;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 80;

    FractionalParticipantEndOfDaySummaryMessage() = default;
    FractionalParticipantEndOfDaySummaryMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number, const std::string& security_symbol, InstrumentType instrument_type, char summary_participant_id, std::uint32_t previous_close_price_date, Decimal last_price, Decimal high_price, Decimal low_price, Decimal open_price, Decimal fractional_total_volume, Tick tick);

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

    // Summary Participant Id: Identifies the Participant whose summary information is provided
    char summary_participant_id() const;
    void set_summary_participant_id(char value);

    // Previous Close Price Date: Represents the date the security last traded. Represented in
    // seconds since Epoch
    std::uint32_t previous_close_price_date() const;
    void set_previous_close_price_date(std::uint32_t value);

    // Last Price: Represents the last price for that security either on a Consolidated or an
    // individual Participant basis at the time it is disseminated. Has implied 6 decimal
    // places
    Decimal last_price() const;
    void set_last_price(Decimal value);

    // High Price: Represents the highest price paid for a security during the trading day. Has
    // implied 6 decimal places
    Decimal high_price() const;
    void set_high_price(Decimal value);

    // Low Price: Represents the lowest price paid for a security during the trading day. Has
    // implied 6 decimal places
    Decimal low_price() const;
    void set_low_price(Decimal value);

    // Open Price: Represents the first qualifying price paid for a security during the trading
    // day. Has implied 6 decimal places
    Decimal open_price() const;
    void set_open_price(Decimal value);

    // Fractional Total Volume: Contains Total Volume of shares traded in a security either on
    // a Consolidated or an individual Participant basis. Has implied 6 decimal places
    Decimal fractional_total_volume() const;
    void set_fractional_total_volume(Decimal value);

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

    bool operator==(const FractionalParticipantEndOfDaySummaryMessage& other) const;
    bool operator!=(const FractionalParticipantEndOfDaySummaryMessage& other) const;

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
    Decimal last_price_{ 0, -6 };
    Decimal high_price_{ 0, -6 };
    Decimal low_price_{ 0, -6 };
    Decimal open_price_{ 0, -6 };
    Decimal fractional_total_volume_{ 0, -6 };
    Tick tick_{};
};

} // namespace siac::cts::output::cta::v2_11_b
