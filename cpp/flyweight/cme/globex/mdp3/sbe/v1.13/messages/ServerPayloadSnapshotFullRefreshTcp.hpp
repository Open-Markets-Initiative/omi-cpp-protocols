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
#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../structs/SnapshotFullRefreshTcpGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// SnapshotFullRefreshTCP
class ServerPayloadSnapshotFullRefreshTcp {
  public:
    static constexpr const char* name = "ServerPayloadSnapshotFullRefreshTcp";

    // the bytes it reads, which it does not own: they must outlive it
    explicit ServerPayloadSnapshotFullRefreshTcp(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every ServerPayloadSnapshotFullRefreshTcp has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 37;
    std::size_t encoded_size() const { return snapshot_full_refresh_tcp_groups_end(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    std::int32_t security_id() const { return wire::read_i32_le(at(9)); }

    std::optional<Decimal> high_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(13)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> low_limit_price() const { return wire::nullable_decimal(wire::read_i64_le(at(21)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    std::optional<Decimal> max_price_variation() const { return wire::nullable_decimal(wire::read_i64_le(at(29)), static_cast<std::int64_t>(9223372036854775807LL), -9); }

    SnapshotFullRefreshTcpGroups snapshot_full_refresh_tcp_groups() const { return SnapshotFullRefreshTcpGroups{ bytes_.subspan(37) }; }

    void print(std::ostream& out) const {
        out << "ServerPayloadSnapshotFullRefreshTcp{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", security_id=";
        out << security_id();
        out << ", high_limit_price=";
        print::optional(out, high_limit_price());
        out << ", low_limit_price=";
        print::optional(out, low_limit_price());
        out << ", max_price_variation=";
        print::optional(out, max_price_variation());
        out << ", snapshot_full_refresh_tcp_groups=";
        snapshot_full_refresh_tcp_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t snapshot_full_refresh_tcp_groups_end() const { return 37 + snapshot_full_refresh_tcp_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const ServerPayloadSnapshotFullRefreshTcp& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
