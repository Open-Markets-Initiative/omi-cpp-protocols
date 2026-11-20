// Cme.Globex.Mdp3.Sbe.v1.9: structs/SnapshotFullRefreshOrderBookLegacyGroups.cpp
#include "SnapshotFullRefreshOrderBookLegacyGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

SnapshotFullRefreshOrderBookLegacyGroups::SnapshotFullRefreshOrderBookLegacyGroups(const GroupSize& group_size, const std::vector<SnapshotFullRefreshOrderBookLegacyGroup>& snapshot_full_refresh_order_book_legacy_group)
  : group_size_(group_size), snapshot_full_refresh_order_book_legacy_group_(snapshot_full_refresh_order_book_legacy_group) {}

const GroupSize& SnapshotFullRefreshOrderBookLegacyGroups::group_size() const { return group_size_; }
GroupSize& SnapshotFullRefreshOrderBookLegacyGroups::group_size() { return group_size_; }
void SnapshotFullRefreshOrderBookLegacyGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SnapshotFullRefreshOrderBookLegacyGroup>& SnapshotFullRefreshOrderBookLegacyGroups::snapshot_full_refresh_order_book_legacy_group() const { return snapshot_full_refresh_order_book_legacy_group_; }
std::vector<SnapshotFullRefreshOrderBookLegacyGroup>& SnapshotFullRefreshOrderBookLegacyGroups::snapshot_full_refresh_order_book_legacy_group() { return snapshot_full_refresh_order_book_legacy_group_; }
void SnapshotFullRefreshOrderBookLegacyGroups::set_snapshot_full_refresh_order_book_legacy_group(const std::vector<SnapshotFullRefreshOrderBookLegacyGroup>& value) { snapshot_full_refresh_order_book_legacy_group_ = value; }

std::size_t SnapshotFullRefreshOrderBookLegacyGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        snapshot_full_refresh_order_book_legacy_group_.clear();
        snapshot_full_refresh_order_book_legacy_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotFullRefreshOrderBookLegacyGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotFullRefreshOrderBookLegacyGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshot_full_refresh_order_book_legacy_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotFullRefreshOrderBookLegacyGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshOrderBookLegacyGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(snapshot_full_refresh_order_book_legacy_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SnapshotFullRefreshOrderBookLegacyGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshot_full_refresh_order_book_legacy_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotFullRefreshOrderBookLegacyGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(snapshot_full_refresh_order_book_legacy_group_);
}

void SnapshotFullRefreshOrderBookLegacyGroups::print(std::ostream& out) const {
    out << "SnapshotFullRefreshOrderBookLegacyGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", snapshot_full_refresh_order_book_legacy_group=";
    print::sequence(out, snapshot_full_refresh_order_book_legacy_group_);
    out << '}';
}

bool SnapshotFullRefreshOrderBookLegacyGroups::operator==(const SnapshotFullRefreshOrderBookLegacyGroups& other) const {
    return group_size_ == other.group_size_
        && snapshot_full_refresh_order_book_legacy_group_ == other.snapshot_full_refresh_order_book_legacy_group_;
}

bool SnapshotFullRefreshOrderBookLegacyGroups::operator!=(const SnapshotFullRefreshOrderBookLegacyGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrderBookLegacyGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
