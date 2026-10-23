#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../structs/SnapshotRefreshTopOrdersGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// SnapshotRefreshTopOrders
class SnapshotRefreshTopOrders {
  public:
    static constexpr const char* name = "SnapshotRefreshTopOrders";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotRefreshTopOrders(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotRefreshTopOrders has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 13;
    std::size_t encoded_size() const { return snapshot_refresh_top_orders_groups_end(); }

    std::chrono::nanoseconds transact_time() const { return std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(at(0)))); }

    MatchEventIndicator match_event_indicator() const { return MatchEventIndicator{ bytes_.subspan(8) }; }

    std::int32_t security_id() const { return wire::read_i32_le(at(9)); }

    SnapshotRefreshTopOrdersGroups snapshot_refresh_top_orders_groups() const { return SnapshotRefreshTopOrdersGroups{ bytes_.subspan(13) }; }

    void print(std::ostream& out) const {
        out << "SnapshotRefreshTopOrders{";
        out << "transact_time=";
        out << transact_time().count();
        out << ", match_event_indicator=";
        match_event_indicator().print(out);
        out << ", security_id=";
        out << security_id();
        out << ", snapshot_refresh_top_orders_groups=";
        snapshot_refresh_top_orders_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t snapshot_refresh_top_orders_groups_end() const { return 13 + snapshot_refresh_top_orders_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotRefreshTopOrders& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
