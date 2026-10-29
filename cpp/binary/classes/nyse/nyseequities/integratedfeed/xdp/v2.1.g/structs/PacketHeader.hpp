#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

#include "../enums/DeliveryFlag.hpp"
#include "../structs/SendTime.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    PacketHeader() = default;
    PacketHeader(std::uint16_t packet_size, DeliveryFlag delivery_flag, std::uint8_t message_count, std::uint32_t sequence_number, const SendTime& send_time);

    // Packet Size: The size of the packet in bytes, including this 16 byte packet header
    std::uint16_t packet_size() const;
    void set_packet_size(std::uint16_t value);

    // Delivery Flag: A flag that indicates whether this is an original, retransmitted, or
    // ‘replayed’ message.
    DeliveryFlag delivery_flag() const;
    void set_delivery_flag(DeliveryFlag value);

    // Message Count: The number of messages in this packet
    std::uint8_t message_count() const;
    void set_message_count(std::uint8_t value);

    // Sequence Number: The message sequence number of the first message in this packet
    std::uint32_t sequence_number() const;
    void set_sequence_number(std::uint32_t value);

    // Send Time: The time when this packet was published to the multicast channel
    const SendTime& send_time() const;
    SendTime& send_time();
    void set_send_time(const SendTime& value);

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
    DeliveryFlag delivery_flag_{};
    std::uint8_t message_count_{};
    std::uint32_t sequence_number_{};
    SendTime send_time_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
