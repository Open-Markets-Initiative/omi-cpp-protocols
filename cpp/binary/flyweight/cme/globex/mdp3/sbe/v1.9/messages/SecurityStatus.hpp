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
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/SecurityTradingEvent.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// SecurityStatus
class SecurityStatus {
  public:
    static constexpr const char* name = "SecurityStatus";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityStatus(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityStatus has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    static constexpr std::size_t fixed_size = 30;
    std::size_t encoded_size() const { return 30; }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::string_view security_group() const { return view::text(at(8), 6, '\0'); }

    std::string_view asset() const { return view::text(at(14), 6, '\0'); }

    std::optional<std::int32_t> security_id_optional() const { return wire::nullable(wire::read_i32_le(at(20)), static_cast<std::int32_t>(2147483647LL)); }

    std::optional<std::uint16_t> trade_date() const { return wire::nullable(wire::read_u16_le(at(24)), static_cast<std::uint16_t>(65535ULL)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(26) }; }

    std::optional<SecurityTradingStatus> security_trading_status() const { return wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(at(27)), static_cast<std::uint8_t>(255ULL)); }

    HaltReason halt_reason() const { return static_cast<HaltReason>(wire::read_u8(at(28))); }

    SecurityTradingEvent security_trading_event() const { return static_cast<SecurityTradingEvent>(wire::read_u8(at(29))); }

    void print(std::ostream& out) const {
        out << "SecurityStatus{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", security_group=";
        print::text(out, security_group());
        out << ", asset=";
        print::text(out, asset());
        out << ", security_id_optional=";
        print::optional(out, security_id_optional());
        out << ", trade_date=";
        print::optional(out, trade_date());
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", security_trading_status=";
        print::optional(out, security_trading_status());
        out << ", halt_reason=";
        out << halt_reason();
        out << ", security_trading_event=";
        out << security_trading_event();
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityStatus& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
