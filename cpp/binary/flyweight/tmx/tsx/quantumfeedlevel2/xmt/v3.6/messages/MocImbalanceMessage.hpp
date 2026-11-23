// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MocImbalanceMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>
#include <string_view>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/ImbalanceSide.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MarketOrderImbalanceSide.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class MocImbalanceMessage {
  public:
    static constexpr const char* name = "MocImbalanceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MocImbalanceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MocImbalanceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 62;
    static constexpr std::size_t fixed_size = 62;
    std::size_t encoded_size() const { return 62; }

    std::string_view symbol() const { return view::text(at(0), 12, ' '); }

    ImbalanceSide imbalance_side() const { return static_cast<ImbalanceSide>(wire::read_char(at(12))); }

    std::optional<std::uint32_t> imbalance_volume() const { return wire::nullable(wire::read_u32_le(at(13)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(17)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<Decimal> imbalance_reference_price() const { return wire::nullable_decimal(wire::read_u64_le(at(25)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<std::uint32_t> paired_volume() const { return wire::nullable(wire::read_u32_le(at(33)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::uint32_t> market_order_imbalance_volume() const { return wire::nullable(wire::read_u32_le(at(37)), static_cast<std::uint32_t>(0ULL)); }

    MarketOrderImbalanceSide market_order_imbalance_side() const { return static_cast<MarketOrderImbalanceSide>(wire::read_char(at(41))); }

    std::optional<Decimal> near_indicative_closing_price() const { return wire::nullable_decimal(wire::read_u64_le(at(42)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<Decimal> far_indicative_closing_price() const { return wire::nullable_decimal(wire::read_u64_le(at(50)), static_cast<std::uint64_t>(0ULL), -6); }

    std::optional<Decimal> price_variation() const { return wire::nullable_decimal(wire::read_u32_le(at(58)), static_cast<std::uint32_t>(0ULL), -2); }

    void print(std::ostream& out) const {
        out << "MocImbalanceMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", imbalance_side=";
        out << imbalance_side();
        out << ", imbalance_volume=";
        print::optional(out, imbalance_volume());
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << ", imbalance_reference_price=";
        print::optional(out, imbalance_reference_price());
        out << ", paired_volume=";
        print::optional(out, paired_volume());
        out << ", market_order_imbalance_volume=";
        print::optional(out, market_order_imbalance_volume());
        out << ", market_order_imbalance_side=";
        out << market_order_imbalance_side();
        out << ", near_indicative_closing_price=";
        print::optional(out, near_indicative_closing_price());
        out << ", far_indicative_closing_price=";
        print::optional(out, far_indicative_closing_price());
        out << ", price_variation=";
        print::optional(out, price_variation());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MocImbalanceMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
