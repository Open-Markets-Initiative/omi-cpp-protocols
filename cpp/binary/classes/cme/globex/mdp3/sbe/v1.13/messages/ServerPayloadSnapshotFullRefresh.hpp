#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MdSecurityTradingStatus.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/SnapshotFullRefreshGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class ServerTcpMessageVisitor;

// SnapshotFullRefresh
class ServerPayloadSnapshotFullRefresh : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::SnapshotFullRefresh;

    ServerPayloadSnapshotFullRefresh() = default;
    ServerPayloadSnapshotFullRefresh(std::uint32_t last_msg_seq_num_processed, std::uint32_t tot_num_reports, std::int32_t security_id, std::uint32_t rpt_seq, std::chrono::nanoseconds transact_time, std::chrono::nanoseconds last_update_time, std::optional<std::uint16_t> trade_date, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, const SnapshotFullRefreshGroups& snapshot_full_refresh_groups);

    // Last Msg Seq Num Processed: Sequence number of the last Incremental feed packet
    // processed. This value is used to synchronize the snapshot loop with the real-time feed
    std::uint32_t last_msg_seq_num_processed() const;
    void set_last_msg_seq_num_processed(std::uint32_t value);

    // Tot Num Reports: Total number of messages replayed in the loop
    std::uint32_t tot_num_reports() const;
    void set_tot_num_reports(std::uint32_t value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Rpt Seq: Sequence number of the last Market Data entry processed for the instrument
    std::uint32_t rpt_seq() const;
    void set_rpt_seq(std::uint32_t value);

    // Transact Time: Start of event processing time in number of nanoseconds since Unix epoch
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Last Update Time: UTC Date and time of last Security Definition add, update or delete on
    // a given Market Data channel
    std::chrono::nanoseconds last_update_time() const;
    void set_last_update_time(std::chrono::nanoseconds value);

    // Trade Date: Trade Session Date
    std::optional<std::uint16_t> trade_date() const;
    void set_trade_date(std::optional<std::uint16_t> value);

    // Md Security Trading Status: Identifies the current trading state of the instrument
    std::optional<MdSecurityTradingStatus> md_security_trading_status() const;
    void set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value);

    // High Limit Price: Upper price threshold for the instrument
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: Lower price threshold for the instrument
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: Differential value for price banding
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // Snapshot Full Refresh Groups: NoMDEntries Block
    const SnapshotFullRefreshGroups& snapshot_full_refresh_groups() const;
    SnapshotFullRefreshGroups& snapshot_full_refresh_groups();
    void set_snapshot_full_refresh_groups(const SnapshotFullRefreshGroups& value);

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

    bool operator==(const ServerPayloadSnapshotFullRefresh& other) const;
    bool operator!=(const ServerPayloadSnapshotFullRefresh& other) const;

  private:
    std::uint32_t last_msg_seq_num_processed_{};
    std::uint32_t tot_num_reports_{};
    std::int32_t security_id_{};
    std::uint32_t rpt_seq_{};
    std::chrono::nanoseconds transact_time_{};
    std::chrono::nanoseconds last_update_time_{};
    std::optional<std::uint16_t> trade_date_{};
    std::optional<MdSecurityTradingStatus> md_security_trading_status_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    SnapshotFullRefreshGroups snapshot_full_refresh_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
