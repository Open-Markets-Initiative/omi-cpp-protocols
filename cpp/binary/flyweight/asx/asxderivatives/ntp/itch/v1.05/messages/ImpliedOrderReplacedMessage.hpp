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
#include "../common/Decimal.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message notifies the subscriber that an existing implied order is to be replaced when
// the implied price, volume or priority has changed due to a price or volume movement of
// “real” orders for a side of a single Tradeable Instrument Id
class ImpliedOrderReplacedMessage {
  public:
    static constexpr const char* name = "ImpliedOrderReplacedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ImpliedOrderReplacedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ImpliedOrderReplacedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 39;
    static constexpr std::size_t fixed_size = 39;
    std::size_t encoded_size() const { return 39; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    Side side() const { return static_cast<Side>(wire::read_char(at(10))); }

    std::uint64_t order_id() const { return wire::read_u64_be(at(11)); }

    std::uint64_t order_book_priority() const { return wire::read_u64_be(at(19)); }

    std::uint32_t quantity() const { return wire::read_u32_be(at(27)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(31))), -2); }

    void print(std::ostream& out) const {
        out << "ImpliedOrderReplacedMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", side=";
        out << side();
        out << ", order_id=";
        out << order_id();
        out << ", order_book_priority=";
        out << order_book_priority();
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

inline std::ostream& operator<<(std::ostream& out, const ImpliedOrderReplacedMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
