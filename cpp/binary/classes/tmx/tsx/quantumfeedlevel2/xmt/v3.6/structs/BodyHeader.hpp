// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: structs/BodyHeader.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/MsgType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Xmt Body Header
class BodyHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 3;

    BodyHeader() = default;
    BodyHeader(std::uint16_t msg_length, MsgType msg_type);

    // Msg Length: Length of this message
    std::uint16_t msg_length() const;
    void set_msg_length(std::uint16_t value);

    // Msg Type: Msg Type
    MsgType msg_type() const;
    void set_msg_type(MsgType value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BodyHeader& other) const;
    bool operator!=(const BodyHeader& other) const;

  private:
    std::uint16_t msg_length_{};
    MsgType msg_type_{};
};

std::ostream& operator<<(std::ostream& out, const BodyHeader& value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
