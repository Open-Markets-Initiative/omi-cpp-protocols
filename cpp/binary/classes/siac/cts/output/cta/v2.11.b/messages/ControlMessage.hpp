#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ControlMessageType.hpp"
#include "../messages/ControlMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::cts::output::cta::v2_11_b {

class Visitor;
class ControlMessagePayloadVisitor;

// Control Category
class ControlMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::Control;

    ControlMessage() = default;
    ControlMessage(const ControlMessage& other);
    ControlMessage& operator=(const ControlMessage& other);
    ControlMessage(ControlMessage&& other) noexcept = default;
    ControlMessage& operator=(ControlMessage&& other) noexcept = default;
    ~ControlMessage() = default;

    // Control Message Type: Identifies the type of Control message
    ControlMessageType control_message_type() const;
    void set_control_message_type(ControlMessageType value);

    // Control Message Payload: Branch
    const ControlMessagePayload* control_message_payload() const;
    ControlMessagePayload* control_message_payload();
    void set_control_message_payload(std::unique_ptr<ControlMessagePayload> value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const ControlMessage& other) const;
    bool operator!=(const ControlMessage& other) const;

  private:
    ControlMessageType control_message_type_{};
    std::unique_ptr<ControlMessagePayload> control_message_payload_{};
};

} // namespace siac::cts::output::cta::v2_11_b
