#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// SoupBinTCP Packet sent by the client
class ClientPacket {
  public:
    static constexpr const char* name = "ClientPacket";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ClientPacket(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ClientPacket has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 0;
    static constexpr std::size_t fixed_size = 0;
    std::size_t encoded_size() const { return 0; }

    void print(std::ostream& out) const {
        out << "ClientPacket{";
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ClientPacket& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
