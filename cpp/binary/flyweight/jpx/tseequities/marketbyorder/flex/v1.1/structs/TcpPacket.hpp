#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/TcpPacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Jpx Flex Tcp Packet
class TcpPacket {
  public:
    static constexpr const char* name = "TcpPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TcpPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TcpPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    TcpPacketHeader tcp_packet_header() const { return TcpPacketHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "TcpPacket{";
        out << "tcp_packet_header=";
        tcp_packet_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TcpPacket& value) {
    value.print(out);
    return out;
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
