#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

class PacketHeader {
  public:
    static constexpr const char* name = "PacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    static constexpr std::size_t fixed_size = 8;
    std::size_t encoded_size() const { return 8; }

    std::uint16_t length() const { return wire::read_u16_le(at(0)); }

    std::uint8_t message_count() const { return wire::read_u8(at(2)); }

    std::uint8_t unit() const { return wire::read_u8(at(3)); }

    std::uint32_t sequence() const { return wire::read_u32_le(at(4)); }

    void print(std::ostream& out) const {
        out << "PacketHeader{";
        out << "length=";
        out << length();
        out << ", message_count=";
        out << static_cast<int>(message_count());
        out << ", unit=";
        out << static_cast<int>(unit());
        out << ", sequence=";
        out << sequence();
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

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
