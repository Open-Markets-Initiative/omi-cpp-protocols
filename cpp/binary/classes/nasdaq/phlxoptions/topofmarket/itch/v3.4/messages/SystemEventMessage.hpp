#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../enums/EventCode.hpp"
#include "../messages/SequencedMessage.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

class SequencedMessageVisitor;

// The system event message type is used to signal a market or data feed handler event.
class SystemEventMessage : public SequencedMessage {
  public:
    // The code that selects this message
    static constexpr SequencedMessageCode message_type = SequencedMessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 7;

    SystemEventMessage() = default;
    SystemEventMessage(std::chrono::nanoseconds nanoseconds, EventCode event_code, std::uint8_t version, std::uint8_t subversion);

    // Nanoseconds: The sub-second portion of the time, in nanoseconds (0-999999999). The
    // second portion of the time is obtained from the most recent timestamp message.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Event Code: Refer to System Event Codes below
    EventCode event_code() const;
    void set_event_code(EventCode value);

    // Version: Version of this interface. Currently set to 3.
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Subversion: Sub-version of this interface. Currently set to 0.
    std::uint8_t subversion() const;
    void set_subversion(std::uint8_t value);

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
    std::uint8_t version_{};
    std::uint8_t subversion_{};
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
