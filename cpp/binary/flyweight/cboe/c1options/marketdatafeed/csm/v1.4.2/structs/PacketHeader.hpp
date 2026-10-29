#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::uint8_t version() const { return wire::read_u8(at(0)); }

    std::uint16_t packet_length() const { return wire::read_u16_be(at(1)); }

    std::uint64_t sending_time() const { return wire::read_u64_be(at(3)); }

    std::uint8_t message_count() const { return wire::read_u8(at(11)); }

    std::uint32_t first_msg_seq_num() const { return wire::read_u32_be(at(12)); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "version=";
        out << static_cast<int>(version());
        out << ", packet_length=";
        out << packet_length();
        out << ", sending_time=";
        out << sending_time();
        out << ", message_count=";
        out << static_cast<int>(message_count());
        out << ", first_msg_seq_num=";
        out << first_msg_seq_num();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
