#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 8;

    PacketHeader() = default;
    PacketHeader(std::uint16_t length, std::uint8_t message_count, std::uint8_t unit, std::uint32_t sequence);

    // Length: Length of entire block of messages. Includes this header and Message Count
    // messages to follow
    std::uint16_t length() const;
    void set_length(std::uint16_t value);

    // Message Count: Number of messages to follow this header
    std::uint8_t message_count() const;
    void set_message_count(std::uint8_t value);

    // Unit: Unit that applies to messages included in this header
    std::uint8_t unit() const;
    void set_unit(std::uint8_t value);

    // Sequence: Sequence Number of the first message to follow this header
    std::uint32_t sequence() const;
    void set_sequence(std::uint32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PacketHeader& other) const;
    bool operator!=(const PacketHeader& other) const;

  private:
    std::uint16_t length_{};
    std::uint8_t message_count_{};
    std::uint8_t unit_{};
    std::uint32_t sequence_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
