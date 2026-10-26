#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <span>

#include "../common/Wire.hpp"
#include "../common/Print.hpp"
#include "../common/View.hpp"
#include "../structs/GroupSize.hpp"
#include "../groups/IncrementalRefreshLimitsBandingGroup.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// NoMDEntries Block
class IncrementalRefreshLimitsBandingGroups {
  public:
    static constexpr const char* name = "IncrementalRefreshLimitsBandingGroups";

    // the bytes it reads, which it does not own: they must outlive it
    explicit IncrementalRefreshLimitsBandingGroups(std::span<const std::byte> bytes) noexcept : bytes_{ bytes } {}

    std::span<const std::byte> bytes() const noexcept { return bytes_; }

    // the bytes every IncrementalRefreshLimitsBandingGroups has, which a reader checks before it views them
    static constexpr std::size_t minimum_size = 3;
    std::size_t encoded_size() const { return incremental_refresh_limits_banding_group_end(); }

    GroupSize group_size() const { return GroupSize{ bytes_.subspan(0) }; }

    view::entries<IncrementalRefreshLimitsBandingGroup> incremental_refresh_limits_banding_group() const { return view::entries<IncrementalRefreshLimitsBandingGroup>{ bytes_.subspan(3), wire::count(group_size().num_in_group()), wire::count(group_size().block_length()) }; }

    void print(std::ostream& out) const {
        out << "IncrementalRefreshLimitsBandingGroups{";
        out << "group_size=";
        group_size().print(out);
        out << ", incremental_refresh_limits_banding_group=";
        print::sequence(out, incremental_refresh_limits_banding_group());
        out << '}';
    }

  private:
    const std::byte* at(std::size_t offset) const noexcept { return bytes_.data() + offset; }
    std::size_t incremental_refresh_limits_banding_group_end() const { return 3 + incremental_refresh_limits_banding_group().encoded_size(); }

    std::span<const std::byte> bytes_;
};

inline std::ostream& operator<<(std::ostream& out, const IncrementalRefreshLimitsBandingGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
