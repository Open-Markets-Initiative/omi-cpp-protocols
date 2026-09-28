#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// B3 Sbe framing header
class FramingHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 4;

    FramingHeader() = default;
    FramingHeader(std::uint16_t message_length, std::uint16_t encoding_type);

    // Message Length: Overall message length including framing and SBE headers
    std::uint16_t message_length() const;
    void set_message_length(std::uint16_t value);

    // Encoding Type: Identifier of the encoding used in the message payload
    std::uint16_t encoding_type() const;
    void set_encoding_type(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FramingHeader& other) const;
    bool operator!=(const FramingHeader& other) const;

  private:
    std::uint16_t message_length_{};
    std::uint16_t encoding_type_{};
};

std::ostream& operator<<(std::ostream& out, const FramingHeader& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
