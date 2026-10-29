#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/SystemEvent.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

class SequencedMessageVisitor;

// A System Event Message signals a Japannext PTS system-wide event
class SystemEventMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    SystemEventMessage() = default;
    SystemEventMessage(std::chrono::nanoseconds timestamp, SystemEvent system_event);

    // Timestamp: Number of nanoseconds past midnight of the current calendar date
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);
    std::int64_t timestamp_utc(const calendar::Day& day) const;

    // System Event: System event code
    SystemEvent system_event() const;
    void set_system_event(SystemEvent value);

    // SequencedMessage
    SequencedMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(SequencedMessageVisitor& visitor) const override;
    std::unique_ptr<SequencedMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const SequencedMessage& other) const override;

    bool operator==(const SystemEventMessage& other) const;
    bool operator!=(const SystemEventMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    SystemEvent system_event_{};
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
