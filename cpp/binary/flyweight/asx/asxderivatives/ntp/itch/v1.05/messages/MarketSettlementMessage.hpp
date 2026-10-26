#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../common/Decimal.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// This message disseminates the final settlement price of a future or option contracts order
// book for the trade date it pertains to
class MarketSettlementMessage {
  public:
    static constexpr const char* name = "MarketSettlementMessage";

    // the bytes it reads, which it does not own: they must outlive it
    explicit MarketSettlementMessage(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every MarketSettlementMessage has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 54;
    static constexpr std::size_t fixed_size = 54;
    std::size_t encoded_size() const { return 54; }

    std::chrono::nanoseconds nanoseconds() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(at(0)))); }

    std::uint16_t trade_date() const { return wire::read_u16_be(at(4)); }

    std::uint32_t tradeable_instrument_id() const { return wire::read_u32_be(at(6)); }

    Decimal opening_trade() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(10))), -2); }

    Decimal highest_trade() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(18))), -2); }

    Decimal lowest_trade() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(26))), -2); }

    Decimal last_trade() const { return Decimal(static_cast<std::int64_t>(wire::read_i64_be(at(34))), -2); }

    std::uint32_t last_volume() const { return wire::read_u32_be(at(42)); }

    std::uint64_t total_traded_volume() const { return wire::read_u64_be(at(46)); }

    void print(std::ostream& out) const {
        out << "MarketSettlementMessage{";
        out << "nanoseconds=";
        out << nanoseconds().count();
        out << ", trade_date=";
        out << trade_date();
        out << ", tradeable_instrument_id=";
        out << tradeable_instrument_id();
        out << ", opening_trade=";
        out << opening_trade();
        out << ", highest_trade=";
        out << highest_trade();
        out << ", lowest_trade=";
        out << lowest_trade();
        out << ", last_trade=";
        out << last_trade();
        out << ", last_volume=";
        out << last_volume();
        out << ", total_traded_volume=";
        out << total_traded_volume();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const MarketSettlementMessage& value) {
    value.print(out);
    return out;
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
