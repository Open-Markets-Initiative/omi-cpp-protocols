#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cme::globex::mdp3::sbe::v1_8 {

// Cme Mdp Packet Header
class BinaryPacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 12;

    BinaryPacketHeader() = default;
    BinaryPacketHeader(std::uint32_t packet_sequence_number, std::chrono::nanoseconds sending_time);

    // Packet Sequence Number: Packet Sequence Number
    std::uint32_t packet_sequence_number() const;
    void set_packet_sequence_number(std::uint32_t value);

    // Sending Time: Packet Sending Time
    std::chrono::nanoseconds sending_time() const;
    void set_sending_time(std::chrono::nanoseconds value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const BinaryPacketHeader& other) const;
    bool operator!=(const BinaryPacketHeader& other) const;

  private:
    std::uint32_t packet_sequence_number_{};
    std::chrono::nanoseconds sending_time_{};
};

std::ostream& operator<<(std::ostream& out, const BinaryPacketHeader& value);

} // namespace cme::globex::mdp3::sbe::v1_8
