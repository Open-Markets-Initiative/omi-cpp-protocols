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
// book and routed executions to other trading centers. In options a Trade message can also be
// sent when an auction executes against a non-displayed order, such as a contra response.
// Trade messages are necessary to calculate Cboe execution-based data. Trade messages do not
// alter the book and can be ignored if messages are being used solely to build a book. The
// Order ID of a hidden order is obfuscated by default in the Trade message, but may be
// optionally disseminated for a member's own orders upon request.
class TradeLongMessage {
  public:
    static constexpr const char* name = "TradeLongMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeLongMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeLongMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    SideIndicator side_indicator() const { return static_cast<SideIndicator>(wire::read_char(at(12))); }

    std::uint32_t quantity_long() const { return wire::read_u32_le(at(13)); }

    std::string_view symbol() const { return view::text(at(17), 6, ' '); }

    Decimal price_long() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(23))), -4); }

    std::uint64_t execution_id() const { return wire::read_u64_le(at(31)); }

    TradeCondition trade_condition() const { return static_cast<TradeCondition>(wire::read_char(at(39))); }

    void print(std::ostream& out) const {
        out << "TradeLongMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", side_indicator=";
        out << side_indicator();
        out << ", quantity_long=";
        out << quantity_long();
        out << ", symbol=";
        print::text(out, symbol());
        out << ", price_long=";
        out << price_long();
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

inline std::ostream& operator<<(std::ostream& out, const TradeLongMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
