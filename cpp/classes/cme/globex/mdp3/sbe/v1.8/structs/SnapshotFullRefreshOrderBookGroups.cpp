#include "SnapshotFullRefreshOrderBookGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

SnapshotFullRefreshOrderBookGroups::SnapshotFullRefreshOrderBookGroups(const GroupSize& group_size, const std::vector<SnapshotFullRefreshOrderBookGroup>& snapshot_full_refresh_order_book_group)
  : group_size_(group_size), snapshot_full_refresh_order_book_group_(snapshot_full_refresh_order_book_group) {}

const GroupSize& SnapshotFullRefreshOrderBookGroups::group_size() const { return group_size_; }
GroupSize& SnapshotFullRefreshOrderBookGroups::group_size() { return group_size_; }
void SnapshotFullRefreshOrderBookGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SnapshotFullRefreshOrderBookGroup>& SnapshotFullRefreshOrderBookGroups::snapshot_full_refresh_order_book_group() const { return snapshot_full_refresh_order_book_group_; }
std::vector<SnapshotFullRefreshOrderBookGroup>& SnapshotFullRefreshOrderBookGroups::snapshot_full_refresh_order_book_group() { return snapshot_full_refresh_order_book_group_; }
void SnapshotFullRefreshOrderBookGroups::set_snapshot_full_refresh_order_book_group(const std::vector<SnapshotFullRefreshOrderBookGroup>& value) { snapshot_full_refresh_order_book_group_ = value; }

std::size_t SnapshotFullRefreshOrderBookGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        snapshot_full_refresh_order_book_group_.clear();
        snapshot_full_refresh_order_book_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotFullRefreshOrderBookGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotFullRefreshOrderBookGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshot_full_refresh_order_book_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotFullRefreshOrderBookGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshOrderBookGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(snapshot_full_refresh_order_book_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SnapshotFullRefreshOrderBookGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshot_full_refresh_order_book_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotFullRefreshOrderBookGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(snapshot_full_refresh_order_book_group_);
}

void SnapshotFullRefreshOrderBookGroups::print(std::ostream& out) const {
    out << "SnapshotFullRefreshOrderBookGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", snapshot_full_refresh_order_book_group=";
    print::sequence(out, snapshot_full_refresh_order_book_group_);
    out << '}';
}

bool SnapshotFullRefreshOrderBookGroups::operator==(const SnapshotFullRefreshOrderBookGroups& other) const {
    return group_size_ == other.group_size_
        && snapshot_full_refresh_order_book_group_ == other.snapshot_full_refresh_order_book_group_;
}

bool SnapshotFullRefreshOrderBookGroups::operator!=(const SnapshotFullRefreshOrderBookGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrderBookGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
