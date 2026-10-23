#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/IncrementalRefreshTradeSummaryLongGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoMDEntries Block
class IncrementalRefreshTradeSummaryLongGroups {
  public:

    IncrementalRefreshTradeSummaryLongGroups() = default;
    IncrementalRefreshTradeSummaryLongGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshTradeSummaryLongGroup>& incremental_refresh_trade_summary_long_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Incremental Refresh Trade Summary Long Group: Number of Trade Summary entries
    const std::vector<IncrementalRefreshTradeSummaryLongGroup>& incremental_refresh_trade_summary_long_group() const;
    std::vector<IncrementalRefreshTradeSummaryLongGroup>& incremental_refresh_trade_summary_long_group();
    void set_incremental_refresh_trade_summary_long_group(const std::vector<IncrementalRefreshTradeSummaryLongGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const IncrementalRefreshTradeSummaryLongGroups& other) const;
    bool operator!=(const IncrementalRefreshTradeSummaryLongGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<IncrementalRefreshTradeSummaryLongGroup> incremental_refresh_trade_summary_long_group_{};
};

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
