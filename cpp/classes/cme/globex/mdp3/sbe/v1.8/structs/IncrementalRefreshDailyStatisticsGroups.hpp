#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/IncrementalRefreshDailyStatisticsGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// NoMDEntries Block
class IncrementalRefreshDailyStatisticsGroups {
  public:

    IncrementalRefreshDailyStatisticsGroups() = default;
    IncrementalRefreshDailyStatisticsGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshDailyStatisticsGroup>& incremental_refresh_daily_statistics_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Incremental Refresh Daily Statistics Group: Number of entries in Market Data message
    const std::vector<IncrementalRefreshDailyStatisticsGroup>& incremental_refresh_daily_statistics_group() const;
    std::vector<IncrementalRefreshDailyStatisticsGroup>& incremental_refresh_daily_statistics_group();
    void set_incremental_refresh_daily_statistics_group(const std::vector<IncrementalRefreshDailyStatisticsGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshDailyStatisticsGroups& other) const;
    bool operator!=(const IncrementalRefreshDailyStatisticsGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<IncrementalRefreshDailyStatisticsGroup> incremental_refresh_daily_statistics_group_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshDailyStatisticsGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_8
