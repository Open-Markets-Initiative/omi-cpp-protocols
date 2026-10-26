#include "SnapshotFullRefreshGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

SnapshotFullRefreshGroups::SnapshotFullRefreshGroups(const GroupSize& group_size, const std::vector<SnapshotFullRefreshGroup>& snapshot_full_refresh_group)
  : group_size_(group_size), snapshot_full_refresh_group_(snapshot_full_refresh_group) {}

const GroupSize& SnapshotFullRefreshGroups::group_size() const { return group_size_; }
GroupSize& SnapshotFullRefreshGroups::group_size() { return group_size_; }
void SnapshotFullRefreshGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SnapshotFullRefreshGroup>& SnapshotFullRefreshGroups::snapshot_full_refresh_group() const { return snapshot_full_refresh_group_; }
std::vector<SnapshotFullRefreshGroup>& SnapshotFullRefreshGroups::snapshot_full_refresh_group() { return snapshot_full_refresh_group_; }
void SnapshotFullRefreshGroups::set_snapshot_full_refresh_group(const std::vector<SnapshotFullRefreshGroup>& value) { snapshot_full_refresh_group_ = value; }

std::size_t SnapshotFullRefreshGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        snapshot_full_refresh_group_.clear();
        snapshot_full_refresh_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotFullRefreshGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotFullRefreshGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshot_full_refresh_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotFullRefreshGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(snapshot_full_refresh_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SnapshotFullRefreshGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshot_full_refresh_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotFullRefreshGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(snapshot_full_refresh_group_);
}

void SnapshotFullRefreshGroups::print(std::ostream& out) const {
    out << "SnapshotFullRefreshGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", snapshot_full_refresh_group=";
    print::sequence(out, snapshot_full_refresh_group_);
    out << '}';
}

bool SnapshotFullRefreshGroups::operator==(const SnapshotFullRefreshGroups& other) const {
    return group_size_ == other.group_size_
        && snapshot_full_refresh_group_ == other.snapshot_full_refresh_group_;
}

bool SnapshotFullRefreshGroups::operator!=(const SnapshotFullRefreshGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
