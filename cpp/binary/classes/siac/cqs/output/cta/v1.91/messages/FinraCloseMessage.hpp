#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ParticipantId.hpp"
#include "../messages/ControlMessagePayload.hpp"
#include "../structs/ParticipantTimestamp.hpp"

namespace siac::cqs::output::cta::v1_91 {

class ControlMessagePayloadVisitor;

// The FINRA Close message is transmitted by FINRA to CQS to indicate the Close state of FINRA
// Market Maker(s).
class FinraCloseMessage : public ControlMessagePayload {
  public:
    // The code that selects this message
    static constexpr ControlMessagePayloadCode message_type = ControlMessageType::FinraCloseMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 22;

    FinraCloseMessage() = default;
    FinraCloseMessage(ParticipantId participant_id, const ParticipantTimestamp& participant_timestamp, std::uint8_t message_id, std::uint32_t transaction_id, std::int64_t participant_reference_number);

    // Participant Id: Participant or Processor that generated the message
    ParticipantId participant_id() const;
    void set_participant_id(ParticipantId value);

    // Participant Timestamp: Participant Timestamp
    const ParticipantTimestamp& participant_timestamp() const;
    ParticipantTimestamp& participant_timestamp();
    void set_participant_timestamp(const ParticipantTimestamp& value);

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

    bool operator==(const FinraCloseMessage& other) const;
    bool operator!=(const FinraCloseMessage& other) const;

  private:
    ParticipantId participant_id_{};
    ParticipantTimestamp participant_timestamp_{};
    std::uint8_t message_id_{};
    std::uint32_t transaction_id_{};
    std::int64_t participant_reference_number_{};
};

} // namespace siac::cqs::output::cta::v1_91
