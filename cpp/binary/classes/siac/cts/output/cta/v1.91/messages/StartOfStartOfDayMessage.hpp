#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ParticipantId.hpp"
#include "../messages/AdministrativeMessagePayload.hpp"
#include "../structs/Timestamp1.hpp"

namespace siac::cts::output::cta::v1_91 {

class AdministrativeMessagePayloadVisitor;

// The Start of Start of Day message signals the end of Consolidated End of Day Summary and
// Participant End of Day Summary message iterations
class StartOfStartOfDayMessage : public AdministrativeMessagePayload {
  public:
    // The code that selects this message
    static constexpr AdministrativeMessagePayloadCode message_type = AdministrativeMessageType::StartOfStartOfDayMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    StartOfStartOfDayMessage() = default;
    StartOfStartOfDayMessage(ParticipantId participant_id, const Timestamp1& timestamp_1, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number);

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

    bool operator==(const StartOfStartOfDayMessage& other) const;
    bool operator!=(const StartOfStartOfDayMessage& other) const;

  private:
    ParticipantId participant_id_{};
    Timestamp1 timestamp_1_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
};

} // namespace siac::cts::output::cta::v1_91
