#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// An order book is flushed and all orders removed
class OrderBookFlushMessage {
  public:
    static constexpr const char* name = "OrderBookFlushMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookFlushMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderBookFlushMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 14;
    static constexpr std::size_t fixed_size = 14;
    std::size_t encoded_size() const { return 14; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(at(0)))); }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(8)); }

    std::uint32_t order_book() const { return wire::read_u32_be(at(10)); }

    void print(std::ostream& out) const {
        out << "OrderBookFlushMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", tracking_number=";
        out << tracking_number();
        out << ", order_book=";
        out << order_book();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderBookFlushMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
