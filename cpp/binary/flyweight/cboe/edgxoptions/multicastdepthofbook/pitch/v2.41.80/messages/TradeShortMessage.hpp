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
#include "../enums/SideIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/TradeCondition.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// The Trade message provides information about executions of non-displayed orders on the Cboe
// book and routed executions to other trading centers. The Short variant uses a Binary Short
// Price and 2-byte Quantity.
class TradeShortMessage {
  public:
    static constexpr const char* name = "TradeShortMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeShortMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeShortMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 32;
    static constexpr std::size_t fixed_size = 32;
    std::size_t encoded_size() const { return 32; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    SideIndicator side_indicator() const { return static_cast<SideIndicator>(wire::read_char(at(12))); }

    std::uint16_t quantity_short() const { return wire::read_u16_le(at(13)); }

    std::string_view symbol() const { return view::text(at(15), 6, ' '); }

    Decimal price_short() const { return Decimal(static_cast<std::int64_t>(wire::read_u16_le(at(21))), -2); }

    std::uint64_t execution_id() const { return wire::read_u64_le(at(23)); }

    TradeCondition trade_condition() const { return static_cast<TradeCondition>(wire::read_char(at(31))); }

    void print(std::ostream& out) const {
        out << "TradeShortMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", side_indicator=";
        out << side_indicator();
        out << ", quantity_short=";
        out << quantity_short();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", price_short=";
        out << price_short();
        out << ", execution_id=";
        out << execution_id();
        out << ", trade_condition=";
        out << trade_condition();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeShortMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
