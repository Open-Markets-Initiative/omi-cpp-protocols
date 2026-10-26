#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/ControlMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class ControlMessagePayloadVisitor;

// Control Message
class ControlMessage : public ControlMessagePayload {
  public:
    // The code that selects this message
    static constexpr ControlMessagePayloadCode message_type = ControlMessageType::StartOfDay;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    ControlMessage() = default;
    ControlMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number);

    // Message Indicator: Message identifier
    char message_indicator() const;
    void set_message_indicator(char value);

    // Transaction Id: Reserved for Internal Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: The PRN is for optional use by the Participant
    std::uint32_t participant_reference_number() const;
    void set_participant_reference_number(std::uint32_t value);

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

    bool operator==(const ControlMessage& other) const;
    bool operator!=(const ControlMessage& other) const;

  private:
    char message_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
};

} // namespace siac::opra::output::obi::v6_2
