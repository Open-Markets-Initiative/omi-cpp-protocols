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

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// The Trade message provides information about executions of non-displayed orders on the Cboe
// book and routed executions to other trading centers.
class TradeExpandedMessage {
  public:
    static constexpr const char* name = "TradeExpandedMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeExpandedMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeExpandedMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 42;
    static constexpr std::size_t fixed_size = 42;
    std::size_t encoded_size() const { return 42; }

    std::chrono::nanoseconds time_offset() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint64_t order_id() const { return wire::read_u64_le(at(4)); }

    SideIndicator side_indicator() const { return static_cast<SideIndicator>(wire::read_char(at(12))); }

    std::uint32_t long_quantity() const { return wire::read_u32_le(at(13)); }

    std::string_view expanded_symbol() const { return view::text(at(17), 8, ' '); }

    Decimal long_price() const { return Decimal(static_cast<std::int64_t>(wire::read_u64_le(at(25))), -4); }

    std::uint64_t execution_id() const { return wire::read_u64_le(at(33)); }

    TradeCondition trade_condition() const { return static_cast<TradeCondition>(wire::read_char(at(41))); }

    void print(std::ostream& out) const {
        out << "TradeExpandedMessage{";
        out << "time_offset=";
        out << time_offset().count();
        out << ", order_id=";
        out << order_id();
        out << ", side_indicator=";
        out << side_indicator();
        out << ", long_quantity=";
        out << long_quantity();
        out << ", expanded_symbol=";
        print::text(out, expanded_symbol());
        out << ", long_price=";
        out << long_price();
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

inline std::ostream& operator<<(std::ostream& out, const TradeExpandedMessage& value) {
    value.print(out);
    return out;
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
