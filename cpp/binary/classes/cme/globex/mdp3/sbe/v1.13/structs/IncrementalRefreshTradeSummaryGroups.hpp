#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/IncrementalRefreshTradeSummaryGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoMDEntries Block
class IncrementalRefreshTradeSummaryGroups {
  public:

    IncrementalRefreshTradeSummaryGroups() = default;
    IncrementalRefreshTradeSummaryGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshTradeSummaryGroup>& incremental_refresh_trade_summary_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Incremental Refresh Trade Summary Group: Number of Trade Summary entries
    const std::vector<IncrementalRefreshTradeSummaryGroup>& incremental_refresh_trade_summary_group() const;
    std::vector<IncrementalRefreshTradeSummaryGroup>& incremental_refresh_trade_summary_group();
    void set_incremental_refresh_trade_summary_group(const std::vector<IncrementalRefreshTradeSummaryGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshTradeSummaryGroups& other) const;
    bool operator!=(const IncrementalRefreshTradeSummaryGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<IncrementalRefreshTradeSummaryGroup> incremental_refresh_trade_summary_group_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
