// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: structs/FrameHeader.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/AckRequiredPossDup.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Xmt Udp Packet Frame Header
class FrameHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 11;

    FrameHeader() = default;
    FrameHeader(std::uint8_t start_of_frame, char protocol_name, char protocol_version, std::uint16_t message_length, std::uint32_t session_id, AckRequiredPossDup ack_required_poss_dup, std::uint8_t num_body);

    // Start Of Frame: Start of Frame
    std::uint8_t start_of_frame() const;
    void set_start_of_frame(std::uint8_t value);

    // Protocol Name: Protocol Name
    char protocol_name() const;
    void set_protocol_name(char value);

    // Protocol Version: Protocol major version number
    char protocol_version() const;
    void set_protocol_version(char value);

    // Message Length: Length of message from Header to Body inclusive
    std::uint16_t message_length() const;
    void set_message_length(std::uint16_t value);

    // Session Id: Constant Session Id
    std::uint32_t session_id() const;
    void set_session_id(std::uint32_t value);

    // Ack Required Poss Dup: Ack Required Poss Dup
    AckRequiredPossDup ack_required_poss_dup() const;
    void set_ack_required_poss_dup(AckRequiredPossDup value);

    // Num Body: Num Body
    std::uint8_t num_body() const;
    void set_num_body(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FrameHeader& other) const;
    bool operator!=(const FrameHeader& other) const;

  private:
    std::uint8_t start_of_frame_{};
    char protocol_name_{};
    char protocol_version_{};
    std::uint16_t message_length_{};
    std::uint32_t session_id_{};
    AckRequiredPossDup ack_required_poss_dup_{};
    std::uint8_t num_body_{};
};

std::ostream& operator<<(std::ostream& out, const FrameHeader& value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
