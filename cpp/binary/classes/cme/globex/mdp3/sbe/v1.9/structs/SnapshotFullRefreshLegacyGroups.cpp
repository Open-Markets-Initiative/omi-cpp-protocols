// Cme.Globex.Mdp3.Sbe.v1.9: structs/SnapshotFullRefreshLegacyGroups.cpp
#include "SnapshotFullRefreshLegacyGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

SnapshotFullRefreshLegacyGroups::SnapshotFullRefreshLegacyGroups(const GroupSize& group_size, const std::vector<SnapshotFullRefreshLegacyGroup>& snapshot_full_refresh_legacy_group)
  : group_size_(group_size), snapshot_full_refresh_legacy_group_(snapshot_full_refresh_legacy_group) {}

const GroupSize& SnapshotFullRefreshLegacyGroups::group_size() const { return group_size_; }
GroupSize& SnapshotFullRefreshLegacyGroups::group_size() { return group_size_; }
void SnapshotFullRefreshLegacyGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SnapshotFullRefreshLegacyGroup>& SnapshotFullRefreshLegacyGroups::snapshot_full_refresh_legacy_group() const { return snapshot_full_refresh_legacy_group_; }
std::vector<SnapshotFullRefreshLegacyGroup>& SnapshotFullRefreshLegacyGroups::snapshot_full_refresh_legacy_group() { return snapshot_full_refresh_legacy_group_; }
void SnapshotFullRefreshLegacyGroups::set_snapshot_full_refresh_legacy_group(const std::vector<SnapshotFullRefreshLegacyGroup>& value) { snapshot_full_refresh_legacy_group_ = value; }

std::size_t SnapshotFullRefreshLegacyGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        snapshot_full_refresh_legacy_group_.clear();
        snapshot_full_refresh_legacy_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotFullRefreshLegacyGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotFullRefreshLegacyGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshot_full_refresh_legacy_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotFullRefreshLegacyGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshLegacyGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(snapshot_full_refresh_legacy_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SnapshotFullRefreshLegacyGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshot_full_refresh_legacy_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotFullRefreshLegacyGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(snapshot_full_refresh_legacy_group_);
}

void SnapshotFullRefreshLegacyGroups::print(std::ostream& out) const {
    out << "SnapshotFullRefreshLegacyGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", snapshot_full_refresh_legacy_group=";
    print::sequence(out, snapshot_full_refresh_legacy_group_);
    out << '}';
}

bool SnapshotFullRefreshLegacyGroups::operator==(const SnapshotFullRefreshLegacyGroups& other) const {
    return group_size_ == other.group_size_
        && snapshot_full_refresh_legacy_group_ == other.snapshot_full_refresh_legacy_group_;
}

bool SnapshotFullRefreshLegacyGroups::operator!=(const SnapshotFullRefreshLegacyGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshLegacyGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
