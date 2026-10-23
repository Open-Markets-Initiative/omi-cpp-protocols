#include "IncrementalRefreshVolumeGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshVolumeGroups::IncrementalRefreshVolumeGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshVolumeGroup>& incremental_refresh_volume_group)
  : group_size_(group_size), incremental_refresh_volume_group_(incremental_refresh_volume_group) {}

const GroupSize& IncrementalRefreshVolumeGroups::group_size() const { return group_size_; }
GroupSize& IncrementalRefreshVolumeGroups::group_size() { return group_size_; }
void IncrementalRefreshVolumeGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<IncrementalRefreshVolumeGroup>& IncrementalRefreshVolumeGroups::incremental_refresh_volume_group() const { return incremental_refresh_volume_group_; }
std::vector<IncrementalRefreshVolumeGroup>& IncrementalRefreshVolumeGroups::incremental_refresh_volume_group() { return incremental_refresh_volume_group_; }
void IncrementalRefreshVolumeGroups::set_incremental_refresh_volume_group(const std::vector<IncrementalRefreshVolumeGroup>& value) { incremental_refresh_volume_group_ = value; }

std::size_t IncrementalRefreshVolumeGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        incremental_refresh_volume_group_.clear();
        incremental_refresh_volume_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshVolumeGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshVolumeGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_volume_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshVolumeGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshVolumeGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_volume_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshVolumeGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_volume_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshVolumeGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(incremental_refresh_volume_group_);
}

void IncrementalRefreshVolumeGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshVolumeGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", incremental_refresh_volume_group=";
    print::sequence(out, incremental_refresh_volume_group_);
    out << '}';
}

bool IncrementalRefreshVolumeGroups::operator==(const IncrementalRefreshVolumeGroups& other) const {
    return group_size_ == other.group_size_
        && incremental_refresh_volume_group_ == other.incremental_refresh_volume_group_;
}

bool IncrementalRefreshVolumeGroups::operator!=(const IncrementalRefreshVolumeGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshVolumeGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
