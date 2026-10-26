#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SesmPacketType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// SesM packet header
class SesmPacketHeader {
  public:
    static constexpr const char* name = "SesmPacketHeader";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SesmPacketHeader(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SesmPacketHeader has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    std::uint16_t sesm_packet_length() const { return wire::read_u16_le(at(0)); }

    SesmPacketType sesm_packet_type() const { return static_cast<SesmPacketType>(wire::read_char(at(2))); }

    void print(std::ostream& out) const {
        out << "SesmPacketHeader{";
        out << "sesm_packet_length=";
        out << sesm_packet_length();
        out << ", sesm_packet_type=";
        out << sesm_packet_type();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SesmPacketHeader& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
