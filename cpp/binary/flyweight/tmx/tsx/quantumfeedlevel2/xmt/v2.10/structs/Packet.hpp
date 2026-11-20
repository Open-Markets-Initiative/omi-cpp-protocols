// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: structs/Packet.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/FrameHeader.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Xmt Udp Packet
class Packet {
  public:
    static constexpr const char* name = "Packet";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Packet(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Packet has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    FrameHeader frame_header() const { return FrameHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "Packet{";
        out << "frame_header=";
        frame_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Packet& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
