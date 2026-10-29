#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Packet Flags
class PacketFlag {
  public:
    // Bytes of this bitfield on the wire
    static constexpr std::size_t wire_size = 1;

    PacketFlag() = default;
    explicit PacketFlag(std::uint8_t raw);

    // Heartbeat: A Heartbeat is sent if no business level message has been published for more
    // than a second
    bool heartbeat() const;
    void set_heartbeat(bool value);

    // Seq Num Reset: indicates that the channel sequence numbers are being reset to 1
    bool seq_num_reset() const;
    void set_seq_num_reset(bool value);

    // Replay: Packet contains replay messages
    bool replay() const;
    void set_replay(bool value);

    // Test: Packet contains test messages
    bool test() const;
    void set_test(bool value);

    // The whole bitfield as its wire integer
    std::uint8_t raw() const;
    void set_raw(std::uint8_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PacketFlag& other) const;
    bool operator!=(const PacketFlag& other) const;

  private:
    std::uint8_t raw_{};
};

std::ostream& operator<<(std::ostream& out, const PacketFlag& value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
