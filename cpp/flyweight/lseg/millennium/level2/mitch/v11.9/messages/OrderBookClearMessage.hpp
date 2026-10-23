#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/OrderBookClearFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

// Sent to instruct recipients to remove all orders from the order book for the specified
// instrument.
class OrderBookClearMessage {
  public:
    static constexpr const char* name = "OrderBookClearMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookClearMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderBookClearMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::uint32_t nanosecond() const { return wire::read_u32_le(at(0)); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(4)); }

    std::span<const std::byte, 1> reserved_a() const { return bytes_.subspan(8).template first<1>(); }

    std::span<const std::byte, 1> reserved_b() const { return bytes_.subspan(9).template first<1>(); }

    OrderBookClearFlags order_book_clear_flags() const { return OrderBookClearFlags{ bytes_.subspan(10) }; }

    void print(std::ostream& out) const {
        out << "OrderBookClearMessage{";
        out << "nanosecond=";
        out << nanosecond();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", reserved_a=";
        print::hex(out, reserved_a().data(), reserved_a().size());
        out << ", reserved_b=";
        print::hex(out, reserved_b().data(), reserved_b().size());
        out << ", order_book_clear_flags=";
        order_book_clear_flags().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const OrderBookClearMessage& value) {
    value.print(out);
    return out;
}

} // namespace lseg::millennium::level2::mitch::v11_9
