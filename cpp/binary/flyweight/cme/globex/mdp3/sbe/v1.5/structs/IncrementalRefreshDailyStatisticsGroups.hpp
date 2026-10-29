#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSize.hpp"
#include "../groups/IncrementalRefreshDailyStatisticsGroup.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// NoMDEntries Block
class IncrementalRefreshDailyStatisticsGroups {
  public:
    static constexpr const char* name = "IncrementalRefreshDailyStatisticsGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshDailyStatisticsGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshDailyStatisticsGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return incremental_refresh_daily_statistics_group_end(); }

    GroupSize group_size() const { return GroupSize{ bytes_.subspan(0) }; }

    view::entries<IncrementalRefreshDailyStatisticsGroup> incremental_refresh_daily_statistics_group() const { return view::entries<IncrementalRefreshDailyStatisticsGroup>{ bytes_.subspan(3), wire::count(group_size().num_in_group()), wire::count(group_size().block_length()) }; }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshDailyStatisticsGroups{";
        out << "group_size=";
        group_size().print(out);
        out << ", incremental_refresh_daily_statistics_group=";
        print::sequence(out, incremental_refresh_daily_statistics_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t incremental_refresh_daily_statistics_group_end() const { return 3 + incremental_refresh_daily_statistics_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshDailyStatisticsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
