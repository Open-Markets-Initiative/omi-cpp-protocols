#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MessageType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Jpx Flex tag header carrying length prefix and message type discriminator
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 2;

    MessageHeader() = default;
    MessageHeader(std::uint8_t tag_length, MessageType message_type);

    // Tag Length: Length in bytes of the Tag Data including the Message Type byte
    std::uint8_t tag_length() const;
    void set_tag_length(std::uint8_t value);

    // Message Type: First byte of the tag identifying the message type used as dispatch key
    MessageType message_type() const;
    void set_message_type(MessageType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MessageHeader& other) const;
    bool operator!=(const MessageHeader& other) const;

  private:
    std::uint8_t tag_length_{};
    MessageType message_type_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
