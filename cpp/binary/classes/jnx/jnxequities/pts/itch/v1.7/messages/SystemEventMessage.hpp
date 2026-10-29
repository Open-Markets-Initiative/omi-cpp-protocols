#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/Group.hpp"
#include "../enums/SystemEvent.hpp"
#include "../messages/SequencedMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

class SequencedMessageVisitor;

// System Event Messages signal data feed, system and market events.
class SystemEventMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    SystemEventMessage() = default;
    SystemEventMessage(std::chrono::nanoseconds nanoseconds, const std::string& group, SystemEvent system_event);

    // Nanoseconds: Number of nanoseconds since last Timestamp Seconds Message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Group: Orderbook group identifier.
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // System Event: Refer to the System Events table below.
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
    std::chrono::nanoseconds nanoseconds_{};
    std::string group_{};
    SystemEvent system_event_{};
};

} // namespace jnx::jnxequities::pts::itch::v1_7
