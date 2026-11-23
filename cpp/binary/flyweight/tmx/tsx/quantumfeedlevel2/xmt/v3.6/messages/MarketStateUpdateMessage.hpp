// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/MarketStateUpdateMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/MarketState.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

class MarketStateUpdateMessage {
  public:
    static constexpr const char* name = "MarketStateUpdateMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketStateUpdateMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketStateUpdateMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 10;
    static constexpr std::size_t fixed_size = 10;
    std::size_t encoded_size() const { return 10; }

    MarketState market_state() const { return static_cast<MarketState>(wire::read_char(at(0))); }

    std::optional<std::uint8_t> stock_group() const { return wire::nullable(wire::read_u8(at(1)), static_cast<std::uint8_t>(0ULL)); }

    std::optional<std::chrono::nanoseconds> trading_system_time_stamp() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(2)), static_cast<std::uint64_t>(0ULL)); }

    void print(std::ostream& out) const {
        out << "MarketStateUpdateMessage{";
        out << "market_state=";
        out << market_state();
        out << ", stock_group=";
        print::optional(out, stock_group());
        out << ", trading_system_time_stamp=";
        print::optional_duration(out, trading_system_time_stamp());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketStateUpdateMessage& value) {
    value.print(out);
    return out;
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
