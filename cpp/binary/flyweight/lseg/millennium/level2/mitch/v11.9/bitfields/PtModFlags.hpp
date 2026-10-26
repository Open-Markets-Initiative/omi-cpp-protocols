#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Indicates a trade cancellation or amendment
class PtModFlags {
  public:
    static constexpr const char* name = "PtModFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PtModFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    bool canc() const { return (raw() & static_cast<std::uint8_t>(0x1)) != 0; }

    bool amnd() const { return (raw() & static_cast<std::uint8_t>(0x2)) != 0; }

    std::uint8_t unused_6() const { return static_cast<std::uint8_t>((raw() & static_cast<std::uint8_t>(0xFC)) >> 2); }

    void print(std::ostream& out) const {
        out << "PtModFlags{";
        out << "canc=";
        out << (canc() ? "true" : "false");
        out << ", amnd=";
        out << (amnd() ? "true" : "false");
        out << ", unused_6=";
        out << static_cast<unsigned long long>(unused_6());
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PtModFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
