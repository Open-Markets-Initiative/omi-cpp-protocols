#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/ServerPacketHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Soup Bin Tcp Packet sent by the server
class ServerFrame {
  public:
    static constexpr const char* name = "ServerFrame";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerFrame(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerFrame has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    static constexpr std::size_t fixed_size = 3;
    std::size_t encoded_size() const { return 3; }

    ServerPacketHeader server_packet_header() const { return ServerPacketHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "ServerFrame{";
        out << "server_packet_header=";
        server_packet_header().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerFrame& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
