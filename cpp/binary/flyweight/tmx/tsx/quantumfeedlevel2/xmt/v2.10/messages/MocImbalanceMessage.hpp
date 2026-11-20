// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/MocImbalanceMessage.hpp
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

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class MocImbalanceMessage {
  public:
    static constexpr const char* name = "MocImbalanceMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MocImbalanceMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MocImbalanceMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    ImbalanceSide imbalance_side() const { return static_cast<ImbalanceSide>(wire::read_char(at(9))); }

    std::optional<std::uint32_t> imbalance_volume() const { return wire::nullable(wire::read_u32_le(at(10)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::chrono::microseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(14)), static_cast<std::uint64_t>(0ULL)); }

    std::optional<Decimal> imbalance_reference_price() const { return wire::nullable_decimal(wire::read_u64_le(at(22)), static_cast<std::uint64_t>(0ULL), -6); }

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

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
