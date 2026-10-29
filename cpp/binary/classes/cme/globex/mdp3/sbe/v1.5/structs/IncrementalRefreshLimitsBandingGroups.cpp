#include "IncrementalRefreshLimitsBandingGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

IncrementalRefreshLimitsBandingGroups::IncrementalRefreshLimitsBandingGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshLimitsBandingGroup>& incremental_refresh_limits_banding_group)
  : group_size_(group_size), incremental_refresh_limits_banding_group_(incremental_refresh_limits_banding_group) {}

const GroupSize& IncrementalRefreshLimitsBandingGroups::group_size() const { return group_size_; }
GroupSize& IncrementalRefreshLimitsBandingGroups::group_size() { return group_size_; }
void IncrementalRefreshLimitsBandingGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<IncrementalRefreshLimitsBandingGroup>& IncrementalRefreshLimitsBandingGroups::incremental_refresh_limits_banding_group() const { return incremental_refresh_limits_banding_group_; }
std::vector<IncrementalRefreshLimitsBandingGroup>& IncrementalRefreshLimitsBandingGroups::incremental_refresh_limits_banding_group() { return incremental_refresh_limits_banding_group_; }
void IncrementalRefreshLimitsBandingGroups::set_incremental_refresh_limits_banding_group(const std::vector<IncrementalRefreshLimitsBandingGroup>& value) { incremental_refresh_limits_banding_group_ = value; }

std::size_t IncrementalRefreshLimitsBandingGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        incremental_refresh_limits_banding_group_.clear();
        incremental_refresh_limits_banding_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshLimitsBandingGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshLimitsBandingGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_limits_banding_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshLimitsBandingGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshLimitsBandingGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_limits_banding_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshLimitsBandingGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_limits_banding_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshLimitsBandingGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(incremental_refresh_limits_banding_group_);
}

void IncrementalRefreshLimitsBandingGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshLimitsBandingGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", incremental_refresh_limits_banding_group=";
    print::sequence(out, incremental_refresh_limits_banding_group_);
    out << '}';
}

bool IncrementalRefreshLimitsBandingGroups::operator==(const IncrementalRefreshLimitsBandingGroups& other) const {
    return group_size_ == other.group_size_
        && incremental_refresh_limits_banding_group_ == other.incremental_refresh_limits_banding_group_;
}

bool IncrementalRefreshLimitsBandingGroups::operator!=(const IncrementalRefreshLimitsBandingGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshLimitsBandingGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
