#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../common/Day.hpp"
#include "../enums/EventCode.hpp"
#include "../messages/Message.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class Visitor;

// The System Event message is used to signal key market or data feed control events.
class SystemEventMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SystemEventMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 9;

    SystemEventMessage() = default;
    SystemEventMessage(std::uint16_t tracking_number, std::chrono::nanoseconds time_stamp, EventCode event_code);

    // Tracking Number: Nasdaq internal tracking number
    std::uint16_t tracking_number() const;
    void set_tracking_number(std::uint16_t value);

    // Time Stamp: Timestamp
    std::chrono::nanoseconds time_stamp() const;
    void set_time_stamp(std::chrono::nanoseconds value);
    std::int64_t time_stamp_utc(const calendar::Day& day) const;

    // Event Code: Denotes the type of event for which the message is being generated.
    EventCode event_code() const;
    void set_event_code(EventCode value);

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
    std::uint16_t tracking_number_{};
    std::chrono::nanoseconds time_stamp_{};
    EventCode event_code_{};
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
