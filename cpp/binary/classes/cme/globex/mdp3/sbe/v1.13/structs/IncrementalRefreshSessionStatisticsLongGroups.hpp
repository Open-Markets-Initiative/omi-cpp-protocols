#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/IncrementalRefreshSessionStatisticsLongGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoMDEntries Block
class IncrementalRefreshSessionStatisticsLongGroups {
  public:

    IncrementalRefreshSessionStatisticsLongGroups() = default;
    IncrementalRefreshSessionStatisticsLongGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshSessionStatisticsLongGroup>& incremental_refresh_session_statistics_long_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Incremental Refresh Session Statistics Long Group: Number of entries in Market Data
    // message
    const std::vector<IncrementalRefreshSessionStatisticsLongGroup>& incremental_refresh_session_statistics_long_group() const;
    std::vector<IncrementalRefreshSessionStatisticsLongGroup>& incremental_refresh_session_statistics_long_group();
    void set_incremental_refresh_session_statistics_long_group(const std::vector<IncrementalRefreshSessionStatisticsLongGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshSessionStatisticsLongGroups& other) const;
    bool operator!=(const IncrementalRefreshSessionStatisticsLongGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<IncrementalRefreshSessionStatisticsLongGroup> incremental_refresh_session_statistics_long_group_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshSessionStatisticsLongGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
