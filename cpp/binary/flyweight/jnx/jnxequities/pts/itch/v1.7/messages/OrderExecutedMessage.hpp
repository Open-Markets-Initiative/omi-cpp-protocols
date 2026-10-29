#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// Order Executed Message is sent whenever an order in the book is executed in whole or part.
class OrderExecutedMessage {
  public:
    static constexpr const char* name = "OrderExecutedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderExecutedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderExecutedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 24;
    static constexpr std::size_t fixed_size = 24;
    std::size_t encoded_size() const { return 24; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_number() const { return wire::read_u64_be(at(4)); }

    std::uint32_t executed_quantity() const { return wire::read_u32_be(at(12)); }

    std::uint64_t match_number() const { return wire::read_u64_be(at(16)); }

    void print(std::ostream& out) const {
        out << "OrderExecutedMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_number=";
        out << order_number();
        out << ", executed_quantity=";
        out << executed_quantity();
        out << ", match_number=";
        out << match_number();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderExecutedMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_7
