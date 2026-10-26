#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// SnapshotFullRefresh_Orders_MBO_71Message
class SnapshotFullRefreshOrdersMbO71Message {
  public:
    static constexpr const char* name = "SnapshotFullRefreshOrdersMbO71Message";

    // the bytes it reads, which it does not own: they must outlive it
    explicit SnapshotFullRefreshOrdersMbO71Message(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every SnapshotFullRefreshOrdersMbO71Message has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 8;
    std::size_t encoded_size() const { return snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_end(); }

    std::uint64_t security_id() const { return wire::read_u64_le(at(0)); }

    SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups() const { return SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups{ bytes_.subspan(8) }; }

    void print(std::ostream& out) const {
        out << "SnapshotFullRefreshOrdersMbO71Message{";
        out << "security_id=";
        out << security_id();
        out << ", snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups=";
        snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups().print(out);
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_end() const { return 8 + snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrdersMbO71Message& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
