#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../bitfields/PacketFlag.hpp"
#include "../common/Day.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 12;

    PacketHeader() = default;
    PacketHeader(std::uint16_t packet_size, std::uint32_t seq_num, const PacketFlag& packet_flag, std::uint8_t message_count, std::chrono::milliseconds packet_milli);

    // Packet Size: Size of packet in bytes
    std::uint16_t packet_size() const;
    void set_packet_size(std::uint16_t value);

    // Seq Num: Channel specific Sequence number of packet
    std::uint32_t seq_num() const;
    void set_seq_num(std::uint32_t value);

    // Packet Flag: Packet Flags
    const PacketFlag& packet_flag() const;
    PacketFlag& packet_flag();
    void set_packet_flag(const PacketFlag& value);

    // Message Count: Number of messages in packet
    std::uint8_t message_count() const;
    void set_message_count(std::uint8_t value);

    // Packet Milli: Milliseconds since local time midnight (EST/EDT)
    std::chrono::milliseconds packet_milli() const;
    void set_packet_milli(std::chrono::milliseconds value);
    std::int64_t packet_milli_utc(const calendar::Day& day) const;

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
    std::uint16_t packet_size_{};
    std::uint32_t seq_num_{};
    PacketFlag packet_flag_{};
    std::uint8_t message_count_{};
    std::chrono::milliseconds packet_milli_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
