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

// Price Tick Size Messages define a set of price tick size tables.
class PriceTickSizeMessage {
  public:
    static constexpr const char* name = "PriceTickSizeMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PriceTickSizeMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PriceTickSizeMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 16;
    static constexpr std::size_t fixed_size = 16;
    std::size_t encoded_size() const { return 16; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t price_tick_size_table_id() const { return wire::read_u32_be(at(4)); }

    Decimal price_tick_size() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(8))), -1); }

    Decimal price_start() const { return Decimal(static_cast<std::int64_t>(wire::read_u32_be(at(12))), -1); }

    void print(std::ostream& out) const {
        out << "PriceTickSizeMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", price_tick_size_table_id=";
        out << price_tick_size_table_id();
        out << ", price_tick_size=";
        out << price_tick_size();
        out << ", price_start=";
        out << price_start();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PriceTickSizeMessage& value) {
    value.print(out);
    return out;
}

} // namespace jnx::jnxequities::pts::itch::v1_6
