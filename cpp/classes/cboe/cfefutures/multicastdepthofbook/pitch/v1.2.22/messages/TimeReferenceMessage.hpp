#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class Visitor;

// The Time Reference message is used to provide a midnight reference point for recipients of
// the feed. It is sent whenever the system starts up and when the system crosses a midnight
// boundary.
class TimeReferenceMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::TimeReferenceMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 16;

    TimeReferenceMessage() = default;
    TimeReferenceMessage(std::chrono::seconds midnight_reference, std::chrono::seconds time_reference, std::chrono::nanoseconds time_offset, std::uint32_t trade_date);

    // Midnight Reference: Midnight Central Time reference time for subsequent Time messages,
    // expressed as number of whole seconds since the Epoch (Midnight January 1, 1970 UTC).
    std::chrono::seconds midnight_reference() const;
    void set_midnight_reference(std::chrono::seconds value);

    // Time Reference: Number of whole seconds from midnight Central Time.
    std::chrono::seconds time_reference() const;
    void set_time_reference(std::chrono::seconds value);

    // Time Offset: Nanosecond offset from last unit timestamp.
    std::chrono::nanoseconds time_offset() const;
    void set_time_offset(std::chrono::nanoseconds value);

    // Trade Date: Current Trade Date
    std::uint32_t trade_date() const;
    void set_trade_date(std::uint32_t value);

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

    bool operator==(const TimeReferenceMessage& other) const;
    bool operator!=(const TimeReferenceMessage& other) const;

  private:
    std::chrono::seconds midnight_reference_{};
    std::chrono::seconds time_reference_{};
    std::chrono::nanoseconds time_offset_{};
    std::uint32_t trade_date_{};
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
