#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/SnapshotRefreshTopOrdersGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// SnapshotRefreshTopOrders
class ServerPayloadSnapshotRefreshTopOrders : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::SnapshotRefreshTopOrders;

    ServerPayloadSnapshotRefreshTopOrders() = default;
    ServerPayloadSnapshotRefreshTopOrders(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, std::int32_t security_id, const SnapshotRefreshTopOrdersGroups& snapshot_refresh_top_orders_groups);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Snapshot Refresh Top Orders Groups: NoMDEntries Block
    const SnapshotRefreshTopOrdersGroups& snapshot_refresh_top_orders_groups() const;
    SnapshotRefreshTopOrdersGroups& snapshot_refresh_top_orders_groups();
    void set_snapshot_refresh_top_orders_groups(const SnapshotRefreshTopOrdersGroups& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadSnapshotRefreshTopOrders& other) const;
    bool operator!=(const ServerPayloadSnapshotRefreshTopOrders& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    MatchEventIndicator match_event_indicator_{};
    std::int32_t security_id_{};
    SnapshotRefreshTopOrdersGroups snapshot_refresh_top_orders_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
