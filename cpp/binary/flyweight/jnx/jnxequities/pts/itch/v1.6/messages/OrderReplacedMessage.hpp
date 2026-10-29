#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

// Order Replaced Message is sent whenever an order in the book has been replaced.
class OrderReplacedMessage {
  public:
    static constexpr const char* name = "OrderReplacedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderReplacedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderReplacedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 28;
    static constexpr std::size_t fixed_size = 28;
    std::size_t encoded_size() const { return 28; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t original_order_number() const { return wire::read_u64_be(at(4)); }

    std::uint64_t new_order_number() const { return wire::read_u64_be(at(12)); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(20)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(24))), -1); }

    void print(std::ostream& out) const {
        out << "OrderReplacedMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", original_order_number=";
        out << original_order_number();
        out << ", new_order_number=";
        out << new_order_number();
        out << ", quantity=";
        out << quantity();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderReplacedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_6
