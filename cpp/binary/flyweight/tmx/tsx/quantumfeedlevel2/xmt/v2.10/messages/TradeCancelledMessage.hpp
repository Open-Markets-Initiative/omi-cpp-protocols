// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/TradeCancelledMessage.hpp
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

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class TradeCancelledMessage {
  public:
    static constexpr const char* name = "TradeCancelledMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradeCancelledMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradeCancelledMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 21;
    static constexpr std::size_t fixed_size = 21;
    std::size_t encoded_size() const { return 21; }

    std::string_view symbol() const { return view::text(at(0), 9, ' '); }

    std::optional<std::uint32_t> trade_number() const { return wire::nullable(wire::read_u32_le(at(9)), static_cast<std::uint32_t>(0ULL)); }

    std::optional<std::chrono::microseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(at(13)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "TradeCancelledMessage{";
        out << "symbol=";
        print::text(out, symbol());
        out << ", trade_number=";
        print::optional(out, trade_number());
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradeCancelledMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
