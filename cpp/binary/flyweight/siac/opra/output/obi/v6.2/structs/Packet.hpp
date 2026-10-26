#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/BlockHeader.hpp"

namespace siac::opra::output::obi::v6_2 {

// Opra Udp Packet
class Packet {
  public:
    static constexpr const char* name = "Packet";

    // the bytes it reads, which it does not own: they must outlive it
    explicit Packet(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every Packet has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 21;
    static constexpr std::size_t fixed_size = 21;
    std::size_t encoded_size() const { return 21; }

    BlockHeader block_header() const { return BlockHeader{ bytes_.subspan(0) }; }

    void print(std::ostream& out) const {
        out << "Packet{";
        out << "block_header=";
        block_header().print(out);
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

} // namespace siac::opra::output::obi::v6_2
