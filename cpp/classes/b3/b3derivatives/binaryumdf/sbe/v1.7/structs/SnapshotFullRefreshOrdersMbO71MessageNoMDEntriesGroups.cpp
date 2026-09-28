#include "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group)
  : group_size_encoding_(group_size_encoding), snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group) {}

const GroupSizeEncoding& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::group_size_encoding() { return group_size_encoding_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group() const { return snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_; }
std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group() { return snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_; }
void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::set_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group(const std::vector<SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup>& value) { snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_ = value; }

std::size_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = static_cast<std::size_t>(group_size_encoding_.num_in_group());
        const std::size_t block = static_cast<std::size_t>(group_size_encoding_.block_length());
        snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_.clear();
        snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_);
}

void SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::print(std::ostream& out) const {
    out << "SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group=";
    print::sequence(out, snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_);
    out << '}';
}

bool SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::operator==(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_ == other.snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_group_;
}

bool SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups::operator!=(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
