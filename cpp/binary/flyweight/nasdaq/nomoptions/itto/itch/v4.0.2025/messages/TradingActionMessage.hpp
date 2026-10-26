#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Day.hpp"
#include "../enums/CurrentTradingState.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// After the start of system hours, NASDAQ will use the Trading Action message to relay changes
// in trading status for an individual option. Messages will be sent when an option is halted,
// is released for quotation, released for trading, or temporarily suspended for trading on the
// buy or sell side.
class TradingActionMessage {
  public:
    static constexpr const char* name = "TradingActionMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit TradingActionMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every TradingActionMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    static constexpr std::size_t fixed_size = 13;
    std::size_t encoded_size() const { return 13; }

    std::uint16_t tracking_number() const { return wire::read_u16_be(at(0)); }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(at(2)))); }
    std::int64_t timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "America/New_York").utc(static_cast<std::int64_t>(timestamp().count())); }

    std::uint32_t option_id() const { return wire::read_u32_be(at(8)); }

    CurrentTradingState current_trading_state() const { return static_cast<CurrentTradingState>(wire::read_char(at(12))); }

    void print(std::ostream& out) const {
        out << "TradingActionMessage{";
        out << "tracking_number=";
        out << tracking_number();
        out << ", timestamp=";
        calendar::print(out, timestamp().count(), 1, "America/New_York");
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

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
