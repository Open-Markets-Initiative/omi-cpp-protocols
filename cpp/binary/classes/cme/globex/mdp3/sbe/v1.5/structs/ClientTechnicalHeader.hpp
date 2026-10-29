#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_5 {

// Cme Technical Header sent by the firm to Cme
class ClientTechnicalHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 14;

    ClientTechnicalHeader() = default;
    ClientTechnicalHeader(std::uint16_t encoding_type, std::uint32_t message_sequence_number, std::chrono::nanoseconds tcp_sending_time);

    // Encoding Type: Encoding Type
    std::uint16_t encoding_type() const;
    void set_encoding_type(std::uint16_t value);

    // Message Sequence Number: Packet Sequence Number
    std::uint32_t message_sequence_number() const;
    void set_message_sequence_number(std::uint32_t value);

    // Tcp Sending Time: Packet Sending Time, nanoseconds since the Unix epoch
    std::chrono::nanoseconds tcp_sending_time() const;
    void set_tcp_sending_time(std::chrono::nanoseconds value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ClientTechnicalHeader& other) const;
    bool operator!=(const ClientTechnicalHeader& other) const;

  private:
    std::uint16_t encoding_type_{};
    std::uint32_t message_sequence_number_{};
    std::chrono::nanoseconds tcp_sending_time_{};
};

std::ostream& operator<<(std::ostream& out, const ClientTechnicalHeader& value);

} // namespace cme::globex::mdp3::sbe::v1_5
