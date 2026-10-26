#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ParticipantId.hpp"
#include "../messages/ControlMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v2_11_b {

class ControlMessagePayloadVisitor;

// Transmitted over the multicast lines to advise all Data Recipients that there are no further
// messages to be transmitted for the day
class EndOfDayMessage : public ControlMessagePayload {
  public:
    // The code that selects this message
    static constexpr ControlMessagePayloadCode message_type = ControlMessageType::EndOfDay;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    EndOfDayMessage() = default;
    EndOfDayMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number);

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

    // ControlMessagePayload
    ControlMessagePayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ControlMessagePayloadVisitor& visitor) const override;
    std::unique_ptr<ControlMessagePayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ControlMessagePayload& other) const override;

    bool operator==(const EndOfDayMessage& other) const;
    bool operator!=(const EndOfDayMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
};

} // namespace siac::cts::output::cta::v2_11_b
