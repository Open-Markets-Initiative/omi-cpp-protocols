#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/ControlMessageType.hpp"
#include "../messages/ControlMessagePayload.hpp"
#include "../messages/Message.hpp"

namespace siac::opra::output::obi::v6_2 {

class Visitor;
class ControlMessagePayloadVisitor;

// Control Message
class ControlCategory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::Control;

    ControlCategory() = default;
    ControlCategory(const ControlCategory& other);
    ControlCategory& operator=(const ControlCategory& other);
    ControlCategory(ControlCategory&& other) noexcept = default;
    ControlCategory& operator=(ControlCategory&& other) noexcept = default;
    ~ControlCategory() = default;

    // Control Message Type: Control Message Type
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

    bool operator==(const ControlCategory& other) const;
    bool operator!=(const ControlCategory& other) const;

  private:
    ControlMessageType control_message_type_{};
    std::unique_ptr<ControlMessagePayload> control_message_payload_{};
};

} // namespace siac::opra::output::obi::v6_2
