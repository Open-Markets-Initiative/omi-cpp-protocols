#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/SnapshotFullRefreshTcpGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// SnapshotFullRefreshTCP
class ServerPayloadSnapshotFullRefreshTcp : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::SnapshotFullRefreshTcp;

    ServerPayloadSnapshotFullRefreshTcp() = default;
    ServerPayloadSnapshotFullRefreshTcp(std::chrono::nanoseconds transact_time, const MatchEventIndicator& match_event_indicator, std::int32_t security_id, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, const SnapshotFullRefreshTcpGroups& snapshot_full_refresh_tcp_groups);

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

    // High Limit Price: Upper price threshold for the instrument
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: Lower price threshold for the instrument
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: Differential value for price banding
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // Snapshot Full Refresh Tcp Groups: NoMDEntries Block
    const SnapshotFullRefreshTcpGroups& snapshot_full_refresh_tcp_groups() const;
    SnapshotFullRefreshTcpGroups& snapshot_full_refresh_tcp_groups();
    void set_snapshot_full_refresh_tcp_groups(const SnapshotFullRefreshTcpGroups& value);

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

    bool operator==(const ServerPayloadSnapshotFullRefreshTcp& other) const;
    bool operator!=(const ServerPayloadSnapshotFullRefreshTcp& other) const;

  private:
    std::chrono::nanoseconds transact_time_{};
    MatchEventIndicator match_event_indicator_{};
    std::int32_t security_id_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    SnapshotFullRefreshTcpGroups snapshot_full_refresh_tcp_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
