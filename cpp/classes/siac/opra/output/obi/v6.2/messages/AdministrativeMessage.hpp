#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../messages/AdministrativeMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class AdministrativeMessagePayloadVisitor;

// Administrative Message
class AdministrativeMessage : public AdministrativeMessagePayload {
  public:
    // The code that selects this message
    static constexpr AdministrativeMessagePayloadCode message_type = AdministrativeMessageType::Administrative;

    AdministrativeMessage() = default;
    AdministrativeMessage(char message_indicator, std::uint32_t transaction_id, std::uint32_t participant_reference_number, std::uint16_t message_data_length, const std::string& message_data);

    // Message Indicator: Message identifier
    char message_indicator() const;
    void set_message_indicator(char value);

    // Transaction Id: Reserved for Internal Use only
    std::uint32_t transaction_id() const;
    void set_transaction_id(std::uint32_t value);

    // Participant Reference Number: The PRN is for optional use by the Participant
    std::uint32_t participant_reference_number() const;
    void set_participant_reference_number(std::uint32_t value);

    // Message Data Length: Represents the length of the Message Data field
    std::uint16_t message_data_length() const;
    void set_message_data_length(std::uint16_t value);

    // Message Data: Represents the Message Data field.
    const std::string& message_data() const;
    std::string& message_data();
    void set_message_data(const std::string& value);

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

    bool operator==(const AdministrativeMessage& other) const;
    bool operator!=(const AdministrativeMessage& other) const;

  private:
    char message_indicator_{};
    std::uint32_t transaction_id_{};
    std::uint32_t participant_reference_number_{};
    std::uint16_t message_data_length_{};
    std::string message_data_{};
};

} // namespace siac::opra::output::obi::v6_2
