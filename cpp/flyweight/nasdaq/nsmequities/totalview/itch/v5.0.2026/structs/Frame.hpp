#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/ClientPacketHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {

// Soup Bin Tcp Packet sent by the client
class Frame {
  public:
    static constexpr const char* name = "Frame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Frame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Frame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    ClientPacketHeader client_packet_header() const { return ClientPacketHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "Frame{";
        out << "client_packet_header=";
        client_packet_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const Frame& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2026
