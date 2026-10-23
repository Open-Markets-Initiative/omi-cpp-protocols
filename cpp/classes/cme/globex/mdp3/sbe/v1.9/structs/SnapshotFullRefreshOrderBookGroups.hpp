#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/SnapshotFullRefreshOrderBookGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// NoMDEntries Block
class SnapshotFullRefreshOrderBookGroups {
  public:

    SnapshotFullRefreshOrderBookGroups() = default;
    SnapshotFullRefreshOrderBookGroups(const GroupSize& group_size, const std::vector<SnapshotFullRefreshOrderBookGroup>& snapshot_full_refresh_order_book_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Snapshot Full Refresh Order Book Group: Number of entries in Market Data message
    const std::vector<SnapshotFullRefreshOrderBookGroup>& snapshot_full_refresh_order_book_group() const;
    std::vector<SnapshotFullRefreshOrderBookGroup>& snapshot_full_refresh_order_book_group();
    void set_snapshot_full_refresh_order_book_group(const std::vector<SnapshotFullRefreshOrderBookGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SnapshotFullRefreshOrderBookGroups& other) const;
    bool operator!=(const SnapshotFullRefreshOrderBookGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<SnapshotFullRefreshOrderBookGroup> snapshot_full_refresh_order_book_group_{};
};

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrderBookGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_9
