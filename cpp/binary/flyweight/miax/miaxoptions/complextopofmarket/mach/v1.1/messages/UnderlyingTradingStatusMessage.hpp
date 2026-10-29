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
#include "../enums/TradingStatus.hpp"
#include "../enums/EventReason.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// This message format will be used to notify firms of changes to the trading status of all the
// options of an underlying
class UnderlyingTradingStatusMessage {
  public:
    static constexpr const char* name = "UnderlyingTradingStatusMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit UnderlyingTradingStatusMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every UnderlyingTradingStatusMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 25;
    static constexpr std::size_t fixed_size = 25;
    std::size_t encoded_size() const { return 25; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::string_view underlying_symbol() const { return view::text(at(4), 11, ' '); }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_char(at(15))); }

    EventReason event_reason() const { return static_cast<EventReason>(wire::read_char(at(16))); }

    std::uint32_t seconds_part() const { return wire::read_u32_le(at(17)); }

    std::uint32_t expected_event_time_nano_seconds_part() const { return wire::read_u32_le(at(21)); }

    void print(std::ostream& out) const {
        out << "UnderlyingTradingStatusMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", underlying_symbol=";
        print::text(out, underlying_symbol());
        out << ", trading_status=";
        out << trading_status();
        out << ", event_reason=";
        out << event_reason();
        out << ", seconds_part=";
        out << seconds_part();
        out << ", expected_event_time_nano_seconds_part=";
        out << expected_event_time_nano_seconds_part();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const UnderlyingTradingStatusMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
