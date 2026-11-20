// Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a: messages/SequenceNumberResetMessage.hpp
#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class Visitor;

// This message is sent to reset the Message Sequence Number at start of day, or in response to
// failures.
class SequenceNumberResetMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::SequenceNumberResetMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 12;

    SequenceNumberResetMessage() = default;
    SequenceNumberResetMessage(std::chrono::seconds source_time, std::chrono::nanoseconds source_time_ns, std::uint8_t product_id, std::uint8_t channel_id, const std::array<std::byte, 2>& reserved_2);

    // Source Time: The time when this msg was generated in the order book, in seconds since
    // Jan 1, 1970 00:00:00 UTC.
    std::chrono::seconds source_time() const;
    void set_source_time(std::chrono::seconds value);

    // Source Time Ns: The nanosecond offset from the SourceTime.
    std::chrono::nanoseconds source_time_ns() const;
    void set_source_time_ns(std::chrono::nanoseconds value);

    // Product Id: The unique ID for this NYSE feed listed in the feed’s client specification.
    std::uint8_t product_id() const;
    void set_product_id(std::uint8_t value);

    // Channel Id: Multicast channel ID of the symbols being provided.
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Reserved 2: Filler
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

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
    std::array<std::byte, 2> reserved_2_{};
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
