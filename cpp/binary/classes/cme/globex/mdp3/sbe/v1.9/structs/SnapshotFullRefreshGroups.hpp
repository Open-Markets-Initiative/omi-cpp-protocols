#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/SnapshotFullRefreshGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// NoMDEntries Block
class SnapshotFullRefreshGroups {
  public:

    SnapshotFullRefreshGroups() = default;
    SnapshotFullRefreshGroups(const GroupSize& group_size, const std::vector<SnapshotFullRefreshGroup>& snapshot_full_refresh_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Snapshot Full Refresh Group: Number of entries in Market Data message
    const std::vector<SnapshotFullRefreshGroup>& snapshot_full_refresh_group() const;
    std::vector<SnapshotFullRefreshGroup>& snapshot_full_refresh_group();
    void set_snapshot_full_refresh_group(const std::vector<SnapshotFullRefreshGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SnapshotFullRefreshGroups& other) const;
    bool operator!=(const SnapshotFullRefreshGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<SnapshotFullRefreshGroup> snapshot_full_refresh_group_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_9
