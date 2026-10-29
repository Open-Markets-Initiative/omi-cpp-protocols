#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/IncrementalRefreshLimitsBandingGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// NoMDEntries Block
class IncrementalRefreshLimitsBandingGroups {
  public:

    IncrementalRefreshLimitsBandingGroups() = default;
    IncrementalRefreshLimitsBandingGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshLimitsBandingGroup>& incremental_refresh_limits_banding_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Incremental Refresh Limits Banding Group: Number of entries in Market Data message
    const std::vector<IncrementalRefreshLimitsBandingGroup>& incremental_refresh_limits_banding_group() const;
    std::vector<IncrementalRefreshLimitsBandingGroup>& incremental_refresh_limits_banding_group();
    void set_incremental_refresh_limits_banding_group(const std::vector<IncrementalRefreshLimitsBandingGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshLimitsBandingGroups& other) const;
    bool operator!=(const IncrementalRefreshLimitsBandingGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<IncrementalRefreshLimitsBandingGroup> incremental_refresh_limits_banding_group_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshLimitsBandingGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_5
