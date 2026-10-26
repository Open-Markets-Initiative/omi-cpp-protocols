#include "SnapshotFullRefreshOrdersMbO71Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

SnapshotFullRefreshOrdersMbO71Message::SnapshotFullRefreshOrdersMbO71Message(std::uint64_t security_id, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups)
  : security_id_(security_id), snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups) {}

std::uint64_t SnapshotFullRefreshOrdersMbO71Message::security_id() const { return security_id_; }
void SnapshotFullRefreshOrdersMbO71Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& SnapshotFullRefreshOrdersMbO71Message::snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups() const { return snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_; }
SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& SnapshotFullRefreshOrdersMbO71Message::snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups() { return snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_; }
void SnapshotFullRefreshOrdersMbO71Message::set_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& value) { snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_ = value; }

MessageCode SnapshotFullRefreshOrdersMbO71Message::type() const { return message_type; }

std::string_view SnapshotFullRefreshOrdersMbO71Message::name() const { return "Snapshot Full Refresh Orders Mb O 71 Message"; }

std::size_t SnapshotFullRefreshOrdersMbO71Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SnapshotFullRefreshOrdersMbO71Message", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SnapshotFullRefreshOrdersMbO71Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotFullRefreshOrdersMbO71Message", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SnapshotFullRefreshOrdersMbO71Message::encoded_size() const {
    return 8 + snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_.encoded_size();
}

void SnapshotFullRefreshOrdersMbO71Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SnapshotFullRefreshOrdersMbO71Message::clone() const {
    return std::make_unique<SnapshotFullRefreshOrdersMbO71Message>(*this);
}

void SnapshotFullRefreshOrdersMbO71Message::print(std::ostream& out) const {
    out << "SnapshotFullRefreshOrdersMbO71Message{";
    out << "security_id=";
    out << security_id_;
    out << ", snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups=";
    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_.print(out);
    out << '}';
}

bool SnapshotFullRefreshOrdersMbO71Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SnapshotFullRefreshOrdersMbO71Message*>(&other);
    return that != nullptr && *this == *that;
}

bool SnapshotFullRefreshOrdersMbO71Message::operator==(const SnapshotFullRefreshOrdersMbO71Message& other) const {
    return security_id_ == other.security_id_
        && snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_ == other.snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_;
}

bool SnapshotFullRefreshOrdersMbO71Message::operator!=(const SnapshotFullRefreshOrdersMbO71Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
