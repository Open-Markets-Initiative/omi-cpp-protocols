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
#include "../bitfields/MatchEventIndicator.hpp"
#include "../enums/WorkupTradingStatus.hpp"
#include "../enums/HaltReason.hpp"
#include "../enums/SecurityTradingEvent.hpp"
#include "../structs/SecurityStatusWorkupGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// SecurityStatusWorkup
class SecurityStatusWorkup {
  public:
    static constexpr const char* name = "SecurityStatusWorkup";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SecurityStatusWorkup(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SecurityStatusWorkup has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 30;
    std::size_t encoded_size() const { return security_status_workup_groups_end(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    std::optional<Decimal> md_entry_px_optional_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(8)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::int32_t security_id() const { return wire::read_i32_le(at(16)); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(20) }; }

    std::optional<std::uint16_t> trade_date() const { return wire::nullable(wire::read_u16_le(at(21)), static_cast<std::uint16_t>(65535ULL)); }

    std::uint32_t trade_link_id() const { return wire::read_u32_le(at(23)); }

    WorkupTradingStatus workup_trading_status() const { return static_cast<WorkupTradingStatus>(wire::read_u8(at(27))); }

    HaltReason halt_reason() const { return static_cast<HaltReason>(wire::read_u8(at(28))); }

    SecurityTradingEvent security_trading_event() const { return static_cast<SecurityTradingEvent>(wire::read_u8(at(29))); }

    SecurityStatusWorkupGroups security_status_workup_groups() const { return SecurityStatusWorkupGroups{ bytes_.subspan(30) }; }

    void print(std::ostream& out) const {
        out << "SecurityStatusWorkup{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", md_entry_px_optional_ex=";
        print::optional(out, md_entry_px_optional_ex());
        out << ", security_id=";
        out << security_id();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", trade_date=";
        print::optional(out, trade_date());
        out << ", trade_link_id=";
        out << trade_link_id();
        out << ", workup_trading_status=";
        out << workup_trading_status();
        out << ", halt_reason=";
        out << halt_reason();
        out << ", security_trading_event=";
        out << security_trading_event();
        out << ", security_status_workup_groups=";
        security_status_workup_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t security_status_workup_groups_end() const { return 30 + security_status_workup_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SecurityStatusWorkup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
