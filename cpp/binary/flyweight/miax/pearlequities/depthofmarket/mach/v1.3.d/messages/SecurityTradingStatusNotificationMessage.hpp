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
#include "../enums/ShortSaleRestriction.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// This message is used to notify firms of changes to the trading status of a particular
// security.
class SecurityTradingStatusNotificationMessage {
  public:
    static constexpr const char* name = "SecurityTradingStatusNotificationMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityTradingStatusNotificationMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityTradingStatusNotificationMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 11;
    static constexpr std::size_t fixed_size = 11;
    std::size_t encoded_size() const { return 11; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(at(0)))); }

    std::uint32_t symbol_id() const { return wire::read_u32_le(at(4)); }

    TradingStatus trading_status() const { return static_cast<TradingStatus>(wire::read_u8(at(8))); }

    MarketState market_state() const { return static_cast<MarketState>(wire::read_u8(at(9))); }

    ShortSaleRestriction short_sale_restriction() const { return static_cast<ShortSaleRestriction>(wire::read_char(at(10))); }

    void print(std::ostream& out) const {
        out << "SecurityTradingStatusNotificationMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", symbol_id=";
        out << symbol_id();
        out << ", trading_status=";
        out << trading_status();
        out << ", market_state=";
        out << market_state();
        out << ", short_sale_restriction=";
        out << short_sale_restriction();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityTradingStatusNotificationMessage& value) {
    value.print(out);
    return out;
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
