#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

class Visitor;

// This message is sent to reset the Message Sequence Number at start of day, or in response to
// failures.
class SequenceNumberResetMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SequenceNumberResetMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 10;

    SequenceNumberResetMessage() = default;
    SequenceNumberResetMessage(std::chrono::seconds source_time, std::chrono::nanoseconds source_time_ns, std::uint8_t product_id, std::uint8_t channel_id);

    // Source Time: The time when this msg was generated in the order book, in secs since
    // 1/1/1970 00:00:00 UTC
    std::chrono::seconds source_time() const;
    void set_source_time(std::chrono::seconds value);

    // Source Time Ns: The nanosecond offset from the Source Time
    std::chrono::nanoseconds source_time_ns() const;
    void set_source_time_ns(std::chrono::nanoseconds value);

    // Product Id: The unique ID for this NYSE feed listed in the feed's client specification.
    std::uint8_t product_id() const;
    void set_product_id(std::uint8_t value);

    // Channel Id: The ID of the multicast channel over which the packet was sent.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

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

    bool operator==(const SequenceNumberResetMessage& other) const;
    bool operator!=(const SequenceNumberResetMessage& other) const;

  private:
    std::chrono::seconds source_time_{};
    std::chrono::nanoseconds source_time_ns_{};
    std::uint8_t product_id_{};
    std::uint8_t channel_id_{};
};

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
