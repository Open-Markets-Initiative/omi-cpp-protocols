#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// B3 Mdp Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    PacketHeader() = default;
    PacketHeader(std::uint8_t channel_id, std::uint8_t packet_reserved, std::uint16_t sequence_version, std::uint32_t sequence_number, std::chrono::nanoseconds sending_time);

    // Channel Id: B3 Channel Id
    std::uint8_t channel_id() const;
    void set_channel_id(std::uint8_t value);

    // Packet Reserved: Packet Reserved Field
    std::uint8_t packet_reserved() const;
    void set_packet_reserved(std::uint8_t value);

    // Sequence Version: Packet Sequence Version
    std::uint16_t sequence_version() const;
    void set_sequence_version(std::uint16_t value);

    // Sequence Number: Packet Sequence Number
    std::uint32_t sequence_number() const;
    void set_sequence_number(std::uint32_t value);

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

    bool operator==(const PacketHeader& other) const;
    bool operator!=(const PacketHeader& other) const;

  private:
    std::uint8_t channel_id_{};
    std::uint8_t packet_reserved_{};
    std::uint16_t sequence_version_{};
    std::uint32_t sequence_number_{};
    std::chrono::nanoseconds sending_time_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
