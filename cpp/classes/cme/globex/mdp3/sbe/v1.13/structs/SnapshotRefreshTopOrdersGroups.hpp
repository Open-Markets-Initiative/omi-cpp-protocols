#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/SnapshotRefreshTopOrdersGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoMDEntries Block
class SnapshotRefreshTopOrdersGroups {
  public:

    SnapshotRefreshTopOrdersGroups() = default;
    SnapshotRefreshTopOrdersGroups(const GroupSize& group_size, const std::vector<SnapshotRefreshTopOrdersGroup>& snapshot_refresh_top_orders_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Snapshot Refresh Top Orders Group: Number of data blocks following
    const std::vector<SnapshotRefreshTopOrdersGroup>& snapshot_refresh_top_orders_group() const;
    std::vector<SnapshotRefreshTopOrdersGroup>& snapshot_refresh_top_orders_group();
    void set_snapshot_refresh_top_orders_group(const std::vector<SnapshotRefreshTopOrdersGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SnapshotRefreshTopOrdersGroups& other) const;
    bool operator!=(const SnapshotRefreshTopOrdersGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<SnapshotRefreshTopOrdersGroup> snapshot_refresh_top_orders_group_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotRefreshTopOrdersGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
