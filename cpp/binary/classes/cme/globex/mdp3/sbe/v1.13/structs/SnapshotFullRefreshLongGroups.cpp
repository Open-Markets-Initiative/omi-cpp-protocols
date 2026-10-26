#include "SnapshotFullRefreshLongGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotFullRefreshLongGroups::SnapshotFullRefreshLongGroups(const GroupSize& group_size, const std::vector<SnapshotFullRefreshLongGroup>& snapshot_full_refresh_long_group)
  : group_size_(group_size), snapshot_full_refresh_long_group_(snapshot_full_refresh_long_group) {}

const GroupSize& SnapshotFullRefreshLongGroups::group_size() const { return group_size_; }
GroupSize& SnapshotFullRefreshLongGroups::group_size() { return group_size_; }
void SnapshotFullRefreshLongGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SnapshotFullRefreshLongGroup>& SnapshotFullRefreshLongGroups::snapshot_full_refresh_long_group() const { return snapshot_full_refresh_long_group_; }
std::vector<SnapshotFullRefreshLongGroup>& SnapshotFullRefreshLongGroups::snapshot_full_refresh_long_group() { return snapshot_full_refresh_long_group_; }
void SnapshotFullRefreshLongGroups::set_snapshot_full_refresh_long_group(const std::vector<SnapshotFullRefreshLongGroup>& value) { snapshot_full_refresh_long_group_ = value; }

std::size_t SnapshotFullRefreshLongGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        snapshot_full_refresh_long_group_.clear();
        snapshot_full_refresh_long_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotFullRefreshLongGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotFullRefreshLongGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshot_full_refresh_long_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotFullRefreshLongGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshLongGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(snapshot_full_refresh_long_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SnapshotFullRefreshLongGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshot_full_refresh_long_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotFullRefreshLongGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(snapshot_full_refresh_long_group_);
}

void SnapshotFullRefreshLongGroups::print(std::ostream& out) const {
    out << "SnapshotFullRefreshLongGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", snapshot_full_refresh_long_group=";
    print::sequence(out, snapshot_full_refresh_long_group_);
    out << '}';
}

bool SnapshotFullRefreshLongGroups::operator==(const SnapshotFullRefreshLongGroups& other) const {
    return group_size_ == other.group_size_
        && snapshot_full_refresh_long_group_ == other.snapshot_full_refresh_long_group_;
}

bool SnapshotFullRefreshLongGroups::operator!=(const SnapshotFullRefreshLongGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshLongGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
