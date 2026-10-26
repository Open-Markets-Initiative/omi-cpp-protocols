#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/SourceVenue.hpp"
#include "../enums/OrderBookType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Sent to instruct recipients to remove all orders from the order book for the specified
// instrument.
class OrderBookClearMessage {
  public:
    static constexpr const char* name = "OrderBookClearMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit OrderBookClearMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every OrderBookClearMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 19;
    static constexpr std::size_t fixed_size = 19;
    std::size_t encoded_size() const { return 19; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    SourceVenue source_venue() const { return static_cast<SourceVenue>(wire::read_u16_le(at(8))); }

    std::uint64_t instrument() const { return wire::read_u64_le(at(10)); }

    OrderBookType order_book_type() const { return static_cast<OrderBookType>(wire::read_u8(at(18))); }

    void print(std::ostream& out) const {
        out << "OrderBookClearMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", source_venue=";
        out << source_venue();
        out << ", instrument=";
        out << instrument();
        out << ", order_book_type=";
        out << order_book_type();
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

} // namespace lseg::lse::level2mbo::gtp::v26_2
