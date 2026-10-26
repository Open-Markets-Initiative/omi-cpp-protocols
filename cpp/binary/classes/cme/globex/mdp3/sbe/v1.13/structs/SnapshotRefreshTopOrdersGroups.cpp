#include "SnapshotRefreshTopOrdersGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotRefreshTopOrdersGroups::SnapshotRefreshTopOrdersGroups(const GroupSize& group_size, const std::vector<SnapshotRefreshTopOrdersGroup>& snapshot_refresh_top_orders_group)
  : group_size_(group_size), snapshot_refresh_top_orders_group_(snapshot_refresh_top_orders_group) {}

const GroupSize& SnapshotRefreshTopOrdersGroups::group_size() const { return group_size_; }
GroupSize& SnapshotRefreshTopOrdersGroups::group_size() { return group_size_; }
void SnapshotRefreshTopOrdersGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SnapshotRefreshTopOrdersGroup>& SnapshotRefreshTopOrdersGroups::snapshot_refresh_top_orders_group() const { return snapshot_refresh_top_orders_group_; }
std::vector<SnapshotRefreshTopOrdersGroup>& SnapshotRefreshTopOrdersGroups::snapshot_refresh_top_orders_group() { return snapshot_refresh_top_orders_group_; }
void SnapshotRefreshTopOrdersGroups::set_snapshot_refresh_top_orders_group(const std::vector<SnapshotRefreshTopOrdersGroup>& value) { snapshot_refresh_top_orders_group_ = value; }

std::size_t SnapshotRefreshTopOrdersGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        snapshot_refresh_top_orders_group_.clear();
        snapshot_refresh_top_orders_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotRefreshTopOrdersGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotRefreshTopOrdersGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshot_refresh_top_orders_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotRefreshTopOrdersGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotRefreshTopOrdersGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(snapshot_refresh_top_orders_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SnapshotRefreshTopOrdersGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshot_refresh_top_orders_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotRefreshTopOrdersGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(snapshot_refresh_top_orders_group_);
}

void SnapshotRefreshTopOrdersGroups::print(std::ostream& out) const {
    out << "SnapshotRefreshTopOrdersGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", snapshot_refresh_top_orders_group=";
    print::sequence(out, snapshot_refresh_top_orders_group_);
    out << '}';
}

bool SnapshotRefreshTopOrdersGroups::operator==(const SnapshotRefreshTopOrdersGroups& other) const {
    return group_size_ == other.group_size_
        && snapshot_refresh_top_orders_group_ == other.snapshot_refresh_top_orders_group_;
}

bool SnapshotRefreshTopOrdersGroups::operator!=(const SnapshotRefreshTopOrdersGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotRefreshTopOrdersGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
