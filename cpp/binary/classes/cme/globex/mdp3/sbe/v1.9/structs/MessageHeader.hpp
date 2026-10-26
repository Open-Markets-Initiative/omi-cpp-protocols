#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../structs/SimpleBinaryHeader.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// Message Size followed by the Simple Binary Header
class MessageHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 10;

    MessageHeader() = default;
    MessageHeader(std::uint16_t message_size, const SimpleBinaryHeader& simple_binary_header);

    // Message Size: Message Size
    std::uint16_t message_size() const;
    void set_message_size(std::uint16_t value);

    // Simple Binary Header: Template ID and length of message root
    const SimpleBinaryHeader& simple_binary_header() const;
    SimpleBinaryHeader& simple_binary_header();
    void set_simple_binary_header(const SimpleBinaryHeader& value);

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
    std::uint16_t message_size_{};
    SimpleBinaryHeader simple_binary_header_{};
};

std::ostream& operator<<(std::ostream& out, const MessageHeader& value);

} // namespace cme::globex::mdp3::sbe::v1_9
