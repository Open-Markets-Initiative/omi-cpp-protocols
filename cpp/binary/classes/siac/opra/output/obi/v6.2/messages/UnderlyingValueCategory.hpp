#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/UnderlyingValueMessageType.hpp"
#include "../messages/Message.hpp"
#include "../messages/UnderlyingValueMessagePayload.hpp"

namespace siac::opra::output::obi::v6_2 {

class Visitor;
class UnderlyingValueMessagePayloadVisitor;

// Underlying Value Message
class UnderlyingValueCategory : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageCategory::UnderlyingValue;

    UnderlyingValueCategory() = default;
    UnderlyingValueCategory(const UnderlyingValueCategory& other);
    UnderlyingValueCategory& operator=(const UnderlyingValueCategory& other);
    UnderlyingValueCategory(UnderlyingValueCategory&& other) noexcept = default;
    UnderlyingValueCategory& operator=(UnderlyingValueCategory&& other) noexcept = default;
    ~UnderlyingValueCategory() = default;

    // Underlying Value Message Type: Underlying Value Message type
    UnderlyingValueMessageType underlying_value_message_type() const;
    void set_underlying_value_message_type(UnderlyingValueMessageType value);

    // Underlying Value Message Payload: Branch
    const UnderlyingValueMessagePayload* underlying_value_message_payload() const;
    UnderlyingValueMessagePayload* underlying_value_message_payload();
    void set_underlying_value_message_payload(std::unique_ptr<UnderlyingValueMessagePayload> value);

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

    bool operator==(const UnderlyingValueCategory& other) const;
    bool operator!=(const UnderlyingValueCategory& other) const;

  private:
    UnderlyingValueMessageType underlying_value_message_type_{};
    std::unique_ptr<UnderlyingValueMessagePayload> underlying_value_message_payload_{};
};

} // namespace siac::opra::output::obi::v6_2
