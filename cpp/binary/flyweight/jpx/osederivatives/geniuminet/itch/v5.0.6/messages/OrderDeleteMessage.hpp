#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/Side.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Sent whenever an order on the book is being deleted. There will be no remaining quantity.
class OrderDeleteMessage {
  public:
    static constexpr const char* name = "OrderDeleteMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderDeleteMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderDeleteMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 17;
    static constexpr std::size_t fixed_size = 17;
    std::size_t encoded_size() const { return 17; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(4)); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(12)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    void print(std::ostream& out) const {
        out << "OrderDeleteMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_id=";
        out << order_id();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", side=";
        out << side();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderDeleteMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
