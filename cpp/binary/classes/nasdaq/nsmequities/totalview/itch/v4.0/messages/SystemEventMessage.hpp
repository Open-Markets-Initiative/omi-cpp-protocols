#pragma once

#include <chrono>
#include <cstddef>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EventCode.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

class SequencedMessageVisitor;

// The system event message type is used to signal a market or data feed handler event.
class SystemEventMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = 'S';
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 5;

    SystemEventMessage() = default;
    SystemEventMessage(std::chrono::nanoseconds nanoseconds, EventCode event_code);

    // Nanoseconds: Nanoseconds portion of the timestamp.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Event Code: See System Event Codes.
    EventCode event_code() const;
    void set_event_code(EventCode value);

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
    EventCode event_code_{};
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
