#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Order Book Clear Flags
class OrderBookClearFlags {
  public:
    static constexpr const char* name = "OrderBookClearFlags";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookClearFlags(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    static constexpr std::size_t minimum_size = 1;
    static constexpr std::size_t fixed_size = 1;
    std::size_t encoded_size() const { return 1; }

    std::uint8_t raw() const { return wire::read_u8(bytes_.data()); }

    std::uint8_t unused_5() const { return static_cast<std::uint8_t>((raw() & static_cast<std::uint8_t>(0x1F)) >> 0); }

    bool firm_quote() const { return (raw() & static_cast<std::uint8_t>(0x20)) != 0; }

    bool private_rfq() const { return (raw() & static_cast<std::uint8_t>(0x40)) != 0; }

    bool unused_1() const { return (raw() & static_cast<std::uint8_t>(0x80)) != 0; }

    void print(std::ostream& out) const {
        out << "OrderBookClearFlags{";
        out << "unused_5=";
        out << static_cast<unsigned long long>(unused_5());
        out << ", firm_quote=";
        out << (firm_quote() ? "true" : "false");
        out << ", private_rfq=";
        out << (private_rfq() ? "true" : "false");
        out << ", unused_1=";
        out << (unused_1() ? "true" : "false");
        out << '}';
    }

  private:

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderBookClearFlags& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
