#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Packet Header
class PacketHeader {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 16;

    PacketHeader() = default;
    PacketHeader(std::uint8_t version, std::uint16_t packet_length, std::uint64_t sending_time, std::uint8_t message_count, std::uint32_t first_msg_seq_num);

    // Version: The version associated with the contents and format of this header. Currently,
    // this will be a constant value of 1.
    std::uint8_t version() const;
    void set_version(std::uint8_t value);

    // Packet Length: Length of the packet including this length field and the version
    std::uint16_t packet_length() const;
    void set_packet_length(std::uint16_t value);

    // Sending Time: The time that this packet was sent. It applies to all messages in this
    // packet.
    std::uint64_t sending_time() const;
    void set_sending_time(std::uint64_t value);

    // Message Count: The number of messages in this packet
    std::uint8_t message_count() const;
    void set_message_count(std::uint8_t value);

    // First Msg Seq Num: The sequence number on the first message in this packet
    std::uint32_t first_msg_seq_num() const;
    void set_first_msg_seq_num(std::uint32_t value);

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
    std::uint8_t version_{};
    std::uint16_t packet_length_{};
    std::uint64_t sending_time_{};
    std::uint8_t message_count_{};
    std::uint32_t first_msg_seq_num_{};
};

std::ostream& operator<<(std::ostream& out, const PacketHeader& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
