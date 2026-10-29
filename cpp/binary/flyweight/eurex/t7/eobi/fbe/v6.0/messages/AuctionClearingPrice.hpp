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
#include "../common/Decimal.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/PotentialSecurityTradingEvent.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

class AuctionClearingPrice {
  public:
    static constexpr const char* name = "AuctionClearingPrice";

    // the bytes it reads, which it does not own: they must outlive it
    explicit AuctionClearingPrice(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every AuctionClearingPrice has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 40;
    static constexpr std::size_t fixed_size = 40;
    std::size_t encoded_size() const { return 40; }

    std::optional<std::chrono::nanoseconds> transact_time() const { return wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(at(0)), static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFFULL)); }

    std::optional<std::int64_t> security_id() const { return wire::nullable(wire::read_i64_le(at(8)), static_cast<std::int64_t>(0x8000000000000000LL)); }

    std::optional<Decimal> last_px() const { return wire::nullable_decimal(wire::read_i64_le(at(16)), static_cast<std::int64_t>(0x8000000000000000LL), -8); }

    std::optional<std::int32_t> last_qty() const { return wire::nullable(wire::read_i32_le(at(24)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<std::int32_t> imbalance_qty() const { return wire::nullable(wire::read_i32_le(at(28)), static_cast<std::int32_t>(0x80000000LL)); }

    std::optional<SecurityTradingStatus> security_trading_status() const { return wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(at(32)), static_cast<std::uint8_t>(0xFFULL)); }

    std::optional<PotentialSecurityTradingEvent> potential_security_trading_event() const { return wire::nullable_enum<PotentialSecurityTradingEvent>(wire::read_u8(at(33)), static_cast<std::uint8_t>(0xFFULL)); }

    std::span<const std::byte, 6> pad6() const { return bytes_.subspan(34).template first<6>(); }

    void print(std::ostream& out) const {
        out << "AuctionClearingPrice{";
        out << "transact_time=";
        print::optional_duration(out, transact_time());
        out << ", security_id=";
        print::optional(out, security_id());
        out << ", last_px=";
        print::optional(out, last_px());
        out << ", last_qty=";
        print::optional(out, last_qty());
        out << ", imbalance_qty=";
        print::optional(out, imbalance_qty());
        out << ", security_trading_status=";
        print::optional(out, security_trading_status());
        out << ", potential_security_trading_event=";
        print::optional(out, potential_security_trading_event());
        out << ", pad6=";
        print::hex(out, pad6().data(), pad6().size());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const AuctionClearingPrice& value) {
    value.print(out);
    return out;
}

} // namespace eurex::t7::eobi::fbe::v6_0
