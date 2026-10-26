#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SesmPacketHeader.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// SesM Tcp Packet
class TcpFrame {
  public:
    static constexpr const char* name = "TcpFrame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TcpFrame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TcpFrame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    SesmPacketHeader sesm_packet_header() const { return SesmPacketHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "TcpFrame{";
        out << "sesm_packet_header=";
        sesm_packet_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TcpFrame& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
