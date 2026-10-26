#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../messages/Message.hpp"
#include "../structs/SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

class Visitor;

// SnapshotFullRefresh_Orders_MBO_71Message
class SnapshotFullRefreshOrdersMbO71Message : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SnapshotFullRefreshOrdersMbO71Message;

    SnapshotFullRefreshOrdersMbO71Message() = default;
    SnapshotFullRefreshOrdersMbO71Message(std::uint64_t security_id, const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Snapshot Full Refresh Orders Mb O 71 Message no M D Entries Groups: noMDEntries Block
    const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups() const;
    SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups();
    void set_snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups(const SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const SnapshotFullRefreshOrdersMbO71Message& other) const;
    bool operator!=(const SnapshotFullRefreshOrdersMbO71Message& other) const;

  private:
    std::uint64_t security_id_{};
    SnapshotFullRefreshOrdersMbO71MessageNoMDEntriesGroups snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
