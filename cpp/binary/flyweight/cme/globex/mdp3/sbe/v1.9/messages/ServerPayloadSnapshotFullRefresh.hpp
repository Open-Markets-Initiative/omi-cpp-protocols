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
#include "../enums/MdSecurityTradingStatus.hpp"
#include "../common/Decimal.hpp"
#include "../structs/SnapshotFullRefreshGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// SnapshotFullRefresh
class ServerPayloadSnapshotFullRefresh {
  public:
    static constexpr const char* name = "ServerPayloadSnapshotFullRefresh";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadSnapshotFullRefresh(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadSnapshotFullRefresh has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 59;
    std::size_t encoded_size() const { return snapshot_full_refresh_groups_end(); }

    std::uint32_t last_msg_seq_num_processed() const { return wire::read_u32_le(at(0)); }

    std::uint32_t tot_num_reports() const { return wire::read_u32_le(at(4)); }

    std::int32_t security_id() const { return wire::read_i32_le(at(8)); }

    std::uint32_t rpt_seq() const { return wire::read_u32_le(at(12)); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(16)))); }

    std::chrono::nanoseconds last_update_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(24)))); }

    std::optional<std::uint16_t> trade_date() const { return wire::nullable(wire::read_u16_le(at(32)), static_cast<std::uint16_t>(65535ULL)); }

    std::optional<MdSecurityTradingStatus> md_security_trading_status() const { return wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(at(34)), static_cast<std::uint8_t>(255ULL)); }

    std::optional<Decimal> high_limit_price_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(35)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> low_limit_price_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(43)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> max_price_variation_ex() const { return wire::nullable_decimal(wire::read_i64_le(at(51)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    SnapshotFullRefreshGroups snapshot_full_refresh_groups() const { return SnapshotFullRefreshGroups{ bytes_.subspan(59) }; }

    void print(std::ostream& out) const {
        out << "ServerPayloadSnapshotFullRefresh{";
        out << "last_msg_seq_num_processed=";
        out << last_msg_seq_num_processed();
        out << ", tot_num_reports=";
        out << tot_num_reports();
        out << ", security_id=";
        out << security_id();
        out << ", rpt_seq=";
        out << rpt_seq();
        out << ", transact_time=";
        out << transact_time().count();
        out << ", last_update_time=";
        out << last_update_time().count();
        out << ", trade_date=";
        print::optional(out, trade_date());
        out << ", md_security_trading_status=";
        print::optional(out, md_security_trading_status());
        out << ", high_limit_price_ex=";
        print::optional(out, high_limit_price_ex());
        out << ", low_limit_price_ex=";
        print::optional(out, low_limit_price_ex());
        out << ", max_price_variation_ex=";
        print::optional(out, max_price_variation_ex());
        out << ", snapshot_full_refresh_groups=";
        snapshot_full_refresh_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t snapshot_full_refresh_groups_end() const { return 59 + snapshot_full_refresh_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadSnapshotFullRefresh& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
