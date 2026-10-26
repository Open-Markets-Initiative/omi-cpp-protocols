#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/EventFlags.hpp"
#include "../common/Decimal.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

// Deep broadcasts a real-time Price Level Update Message each time a displayed price level on
// IEX is updated during the trading day
class PriceLevelSellUpdateMessage {
  public:
    static constexpr const char* name = "PriceLevelSellUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit PriceLevelSellUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every PriceLevelSellUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 29;
    static constexpr std::size_t fixed_size = 29;
    std::size_t encoded_size() const { return 29; }

    EventFlags event_flags() const { return static_cast<EventFlags>(wire::read_u8(at(0))); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(at(1)))); }

    std::string_view symbol() const { return view::text(at(9), 8, ' '); }

    std::uint32_t size() const { return wire::read_u32_le(at(17)); }

    Decimal price() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_le(at(21))), -4); }

    void print(std::ostream& out) const {
        out << "PriceLevelSellUpdateMessage{";
        out << "event_flags=";
        out << event_flags();
        out << ", timestamp=";
        out << timestamp().count();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", size=";
        out << size();
        out << ", price=";
        out << price();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const PriceLevelSellUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace iex::iexequities::deep::snap::v1_6
