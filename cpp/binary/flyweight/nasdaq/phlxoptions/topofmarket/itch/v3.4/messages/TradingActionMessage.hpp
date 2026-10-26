#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/CurrentTradingState.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// The options system uses this administrative message to indicate the current trading status
// of an index or equity option within the options market.
class TradingActionMessage {
  public:
    static constexpr const char* name = "TradingActionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingActionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingActionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 9;
    static constexpr std::size_t fixed_size = 9;
    std::size_t encoded_size() const { return 9; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(4)); }

    CurrentTradingState current_trading_state() const { return static_cast<CurrentTradingState>(wire::read_char(at(8))); }

    void print(std::ostream& out) const {
        out << "TradingActionMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", option_id=";
        out << option_id();
        out << ", current_trading_state=";
        out << current_trading_state();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const TradingActionMessage& value) {
    value.print(out);
    return out;
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
