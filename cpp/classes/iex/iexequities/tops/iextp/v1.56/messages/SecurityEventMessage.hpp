#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/SecurityEvent.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

class Visitor;

// The Security Event Message is used to indicate events that apply to a security
class SecurityEventMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SecurityEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 17;

    SecurityEventMessage() = default;
    SecurityEventMessage(SecurityEvent security_event, std::chrono::nanoseconds timestamp, const std::string& symbol);

    // Security Event: Security event identifier
    SecurityEvent security_event() const;
    void set_security_event(SecurityEvent value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Symbol: Security identifier
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

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

    bool operator==(const SecurityEventMessage& other) const;
    bool operator!=(const SecurityEventMessage& other) const;

  private:
    SecurityEvent security_event_{};
    std::chrono::nanoseconds timestamp_{};
    std::string symbol_{};
};

} // namespace iex::iexequities::tops::iextp::v1_56
