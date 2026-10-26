#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// noMDEntries Block
class SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups {
  public:

    SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups() = default;
    SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group);

    // Group Size Encoding: GroupSizeEncoding
    const GroupSizeEncoding& group_size_encoding() const;
    GroupSizeEncoding& group_size_encoding();
    void set_group_size_encoding(const GroupSizeEncoding& value);

    // Snapshot Full Refresh Orders Mb O 71 Message no M D Entries Group: noMDEntries
    const std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group() const;
    std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group();
    void set_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group(const std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& other) const;
    bool operator!=(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& other) const;

  private:
    GroupSizeEncoding group_size_encoding_{};
    std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup> snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
