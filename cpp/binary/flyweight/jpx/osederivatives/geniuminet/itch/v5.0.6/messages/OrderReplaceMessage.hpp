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
#include "../bitfields/OrderAttributes.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Sent whenever an existing order on the book has been modified. Note: Specification says this
// message is not used, but remains for future reference.
class OrderReplaceMessage {
  public:
    static constexpr const char* name = "OrderReplaceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderReplaceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderReplaceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 35;
    static constexpr std::size_t fixed_size = 35;
    std::size_t encoded_size() const { return 35; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(4)); }

    std::uint32_t order_book_id() const { return wire::read_u32_be(at(12)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(16))); }

    std::uint32_t new_orderbook_position() const { return wire::read_u32_be(at(17)); }

    std::uint64_t quantity() const { return wire::read_u64_be(at(21)); }

    std::int32_t price() const { return wire::read_i32_be(at(29)); }

    OrderAttributes order_attributes() const { return OrderAttributes{ bytes_.subspan(33) }; }

    void print(std::ostream& out) const {
        out << "OrderReplaceMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", order_id=";
        out << order_id();
        out << ", order_book_id=";
        out << order_book_id();
        out << ", side=";
        out << side();
        out << ", new_orderbook_position=";
        out << new_orderbook_position();
        out << ", quantity=";
        out << quantity();
        out << ", price=";
        out << price();
        out << ", order_attributes=";
        order_attributes().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderReplaceMessage& value) {
    value.print(out);
    return out;
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
