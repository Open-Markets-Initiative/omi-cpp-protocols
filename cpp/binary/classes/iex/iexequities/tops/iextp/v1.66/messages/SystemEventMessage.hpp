#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/SystemEvent.hpp"
#include "../messages/Message.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

class Visitor;

// The System Event Message is used to indicate events that apply to the market or the data
// feed
class SystemEventMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    SystemEventMessage() = default;
    SystemEventMessage(SystemEvent system_event, std::chrono::nanoseconds timestamp);

    // System Event: System event identifier
    SystemEvent system_event() const;
    void set_system_event(SystemEvent value);

    // Timestamp: Time stamp of the system event
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

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

    bool operator==(const SystemEventMessage& other) const;
    bool operator!=(const SystemEventMessage& other) const;

  private:
    SystemEvent system_event_{};
    std::chrono::nanoseconds timestamp_{};
};

} // namespace iex::iexequities::tops::iextp::v1_66
