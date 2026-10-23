#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Symbol Status Flags
class SymbolStatusFlags {
  public:
    static constexpr const char* name = "SymbolStatusFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SymbolStatusFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    std::uint8_t unused_5() const { return static_cast<std::uint8_t>((raw() & static_cast<std::uint8_t>(0x1F)) >> 0); }

    bool firm_quote() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    std::uint8_t unused_2() const { return static_cast<std::uint8_t>((raw() & static_cast<std::uint8_t>(0xC0)) >> 6); }

    void print(std::ostream& out) const {
        out << "SymbolStatusFlags{";
        out << "unused_5=";
        out << static_cast<unsigned long long>(unused_5());
        out << ", firm_quote=";
        out << (firm_quote() ? "true" : "false");
        out << ", unused_2=";
        out << static_cast<unsigned long long>(unused_2());
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SymbolStatusFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
