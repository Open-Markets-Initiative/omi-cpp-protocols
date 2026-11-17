// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/InstrumentTradingStatusNotificationMessage.hpp
#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../enums/TradingStatus.hpp"
#include "../enums/MarketState.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Used to notify firms of changes to the trading status of a particular Simple or Complex
// instrument
class InstrumentTradingStatusNotificationMessage {
  public:
    static constexpr const char* name = "InstrumentTradingStatusNotificationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit InstrumentTradingStatusNotificationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every InstrumentTradingStatusNotificationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 14;
    static constexpr std::size_t fixed_size = 14;
    std::size_t encoded_size() const { return 14; }

    std::chrono::nanoseconds timestamp() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::uint32_t instrument_id() const { return wire::read_u32_le(at(8)); }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_u8(at(12))); }

    MarketState market_state() const { return static_cast<MarketState>(wire::read_u8(at(13))); }

    void print(std::ostream& out) const {
        out << "InstrumentTradingStatusNotificationMessage{";
        out << "timestamp=";
        out << timestamp().count();
        out << ", instrument_id=";
        out << instrument_id();
        out << ", trading_status=";
        out << trading_status();
        out << ", market_state=";
        out << market_state();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const InstrumentTradingStatusNotificationMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
