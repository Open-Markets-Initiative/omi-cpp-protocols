#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_13 {

// Cme Technical Header sent by Cme to the firm. Tcp Message Size is the last field so this
// fixed 16 byte header spans everything up to and including the length the reassembly reads.
class ServerTechnicalHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    ServerTechnicalHeader() = default;
    ServerTechnicalHeader(std::uint16_t encoding_type, std::uint32_t message_sequence_number, std::chrono::nanoseconds tcp_sending_time, std::uint16_t tcp_message_size);

    // Encoding Type: Encoding Type
    std::uint16_t encoding_type() const;
    void set_encoding_type(std::uint16_t value);

    // Message Sequence Number: Packet Sequence Number
    std::uint32_t message_sequence_number() const;
    void set_message_sequence_number(std::uint32_t value);

    // Tcp Sending Time: Packet Sending Time, nanoseconds since the Unix epoch
    std::chrono::nanoseconds tcp_sending_time() const;
    void set_tcp_sending_time(std::chrono::nanoseconds value);

    // Tcp Message Size: Message Size
    std::uint16_t tcp_message_size() const;
    void set_tcp_message_size(std::uint16_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ServerTechnicalHeader& other) const;
    bool operator!=(const ServerTechnicalHeader& other) const;

  private:
    std::uint16_t encoding_type_{};
    std::uint32_t message_sequence_number_{};
    std::chrono::nanoseconds tcp_sending_time_{};
    std::uint16_t tcp_message_size_{};
};

std::ostream& operator<<(std::ostream& out, const ServerTechnicalHeader& value);

} // namespace cme::globex::mdp3::sbe::v1_13
