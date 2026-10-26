#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

// Snap message header
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    MessageHeader() = default;
    MessageHeader(std::uint16_t message_length, MessageType message_type);

    // Message Length: Length of message in bytes not including this field
    std::uint16_t message_length() const;
    void set_message_length(std::uint16_t value);

    // Message Type: Code identifying this message type
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
    std::uint16_t message_length_{};
    MessageType message_type_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace iex::iexequities::deepplus::snap::v1_06
