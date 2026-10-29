#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class Visitor;

// In all multicast channels, a Stream ID Message is sent immediately after each packet header
// to uniquely identify the source or Stream ID of the data in the packet.
class StreamIdMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::StreamIdMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 4;

    StreamIdMessage() = default;
    StreamIdMessage(std::uint16_t stream_id, const std::array<std::byte, 2>& reserved_2);

    // Stream Id: Identifies Stream on which this symbol will be updated
    std::uint16_t stream_id() const;
    void set_stream_id(std::uint16_t value);

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

    bool operator==(const StreamIdMessage& other) const;
    bool operator!=(const StreamIdMessage& other) const;

  private:
    std::uint16_t stream_id_{};
    std::array<std::byte, 2> reserved_2_{};
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
