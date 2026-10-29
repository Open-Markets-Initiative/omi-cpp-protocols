#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ExecRestatementReason.hpp"
#include "../enums/OrdStatus.hpp"
#include "../enums/Ordtype.hpp"
#include "../enums/Side.hpp"
#include "../enums/TimeInForce.hpp"
#include "../enums/WorkingIndicator.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/OutboundBusinessHeader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// ExecutionReport_CancelMessage
class ExecutionReportCancelMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionReportCancelMessage;

    ExecutionReportCancelMessage() = default;
    ExecutionReportCancelMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::uint64_t clordid, std::uint64_t secondary_order_id, std::uint64_t security_id, std::uint64_t cum_qty, std::optional<std::uint32_t> account, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::optional<std::chrono::nanoseconds> market_segment_received_time, std::uint64_t order_id, std::optional<std::uint64_t> origclordid, std::uint16_t trade_date, WorkingIndicator working_indicator, std::optional<ExecRestatementReason> exec_restatement_reason, const std::array<std::byte, 4>& offset_100_padding_4, std::optional<std::uint64_t> mass_action_report_id_optional, Ordtype ordtype, TimeInForce time_in_force, std::optional<std::uint16_t> expire_date, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, std::optional<std::chrono::nanoseconds> received_time, const std::array<std::byte, 3>& offset_164_padding_3, std::optional<std::uint8_t> ordtagid, const InvestorId& investor_id, std::optional<std::int32_t> strategy_id, std::optional<std::uint32_t> action_requested_from_session_id, const DeskId& desk_id, const Memo& memo);

    // Outbound Business Header: OutboundBusinessHeader
    const OutboundBusinessHeader& outbound_business_header() const;
    OutboundBusinessHeader& outbound_business_header();
    void set_outbound_business_header(const OutboundBusinessHeader& value);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // Ord Status: ordStatus
    OrdStatus ord_status() const;
    void set_ord_status(OrdStatus value);

    // ClOrdId: clOrdID
    std::uint64_t clordid() const;
    void set_clordid(std::uint64_t value);

    // Secondary Order Id: secondaryOrderID
    std::uint64_t secondary_order_id() const;
    void set_secondary_order_id(std::uint64_t value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Cum Qty: cumQty
    std::uint64_t cum_qty() const;
    void set_cum_qty(std::uint64_t value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Exec Id: execID
    std::uint64_t exec_id() const;
    void set_exec_id(std::uint64_t value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Market Segment Received Time: marketSegmentReceivedTime
    std::optional<std::chrono::nanoseconds> market_segment_received_time() const;
    void set_market_segment_received_time(std::optional<std::chrono::nanoseconds> value);

    // Order Id: orderID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // OrigClOrdId: origClOrdID
    std::optional<std::uint64_t> origclordid() const;
    void set_origclordid(std::optional<std::uint64_t> value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Working Indicator: workingIndicator
    WorkingIndicator working_indicator() const;
    void set_working_indicator(WorkingIndicator value);

    // Exec Restatement Reason: execRestatementReason
    std::optional<ExecRestatementReason> exec_restatement_reason() const;
    void set_exec_restatement_reason(std::optional<ExecRestatementReason> value);

    // Offset 100 Padding 4: 4 bytes padding
    const std::array<std::byte, 4>& offset_100_padding_4() const;
    std::array<std::byte, 4>& offset_100_padding_4();
    void set_offset_100_padding_4(const std::array<std::byte, 4>& value);

    // Mass Action Report Id Optional: massActionReportID
    std::optional<std::uint64_t> mass_action_report_id_optional() const;
    void set_mass_action_report_id_optional(std::optional<std::uint64_t> value);

    // OrdType: ordType
    Ordtype ordtype() const;
    void set_ordtype(Ordtype value);

    // Time In Force: timeInForce
    TimeInForce time_in_force() const;
    void set_time_in_force(TimeInForce value);

    // Expire Date: expireDate
    std::optional<std::uint16_t> expire_date() const;
    void set_expire_date(std::optional<std::uint16_t> value);

    // Order Qty: orderQty
    std::uint64_t order_qty() const;
    void set_order_qty(std::uint64_t value);

    // Price Optional: price
    std::optional<Decimal> price_optional() const;
    void set_price_optional(std::optional<Decimal> value);

    // Stop Px: stopPx
    std::optional<Decimal> stop_px() const;
    void set_stop_px(std::optional<Decimal> value);

    // Min Qty: minQty
    std::optional<std::uint64_t> min_qty() const;
    void set_min_qty(std::optional<std::uint64_t> value);

    // Max Floor: maxFloor
    std::optional<std::uint64_t> max_floor() const;
    void set_max_floor(std::optional<std::uint64_t> value);

    // Received Time: receivedTime
    std::optional<std::chrono::nanoseconds> received_time() const;
    void set_received_time(std::optional<std::chrono::nanoseconds> value);

    // Offset 164 Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& offset_164_padding_3() const;
    std::array<std::byte, 3>& offset_164_padding_3();
    void set_offset_164_padding_3(const std::array<std::byte, 3>& value);

    // OrdTagId: ordTagID
    std::optional<std::uint8_t> ordtagid() const;
    void set_ordtagid(std::optional<std::uint8_t> value);

    // Investor Id: SimpleNewOrderMessage
    const InvestorId& investor_id() const;
    InvestorId& investor_id();
    void set_investor_id(const InvestorId& value);

    // Strategy Id: strategyID
    std::optional<std::int32_t> strategy_id() const;
    void set_strategy_id(std::optional<std::int32_t> value);

    // Action Requested From Session Id: actionRequestedFromSessionID
    std::optional<std::uint32_t> action_requested_from_session_id() const;
    void set_action_requested_from_session_id(std::optional<std::uint32_t> value);

    // Desk Id: deskID data struct
    const DeskId& desk_id() const;
    DeskId& desk_id();
    void set_desk_id(const DeskId& value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

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

    bool operator==(const ExecutionReportCancelMessage& other) const;
    bool operator!=(const ExecutionReportCancelMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    Side side_{};
    OrdStatus ord_status_{};
    std::uint64_t clordid_{};
    std::uint64_t secondary_order_id_{};
    std::uint64_t security_id_{};
    std::uint64_t cum_qty_{};
    std::optional<std::uint32_t> account_{};
    std::uint64_t exec_id_{};
    std::chrono::nanoseconds transact_time_{};
    std::optional<std::chrono::nanoseconds> market_segment_received_time_{};
    std::uint64_t order_id_{};
    std::optional<std::uint64_t> origclordid_{};
    std::uint16_t trade_date_{};
    WorkingIndicator working_indicator_{};
    std::optional<ExecRestatementReason> exec_restatement_reason_{};
    std::array<std::byte, 4> offset_100_padding_4_{};
    std::optional<std::uint64_t> mass_action_report_id_optional_{};
    Ordtype ordtype_{};
    TimeInForce time_in_force_{};
    std::optional<std::uint16_t> expire_date_{};
    std::uint64_t order_qty_{};
    std::optional<Decimal> price_optional_{};
    std::optional<Decimal> stop_px_{};
    std::optional<std::uint64_t> min_qty_{};
    std::optional<std::uint64_t> max_floor_{};
    std::optional<std::chrono::nanoseconds> received_time_{};
    std::array<std::byte, 3> offset_164_padding_3_{};
    std::optional<std::uint8_t> ordtagid_{};
    InvestorId investor_id_{};
    std::optional<std::int32_t> strategy_id_{};
    std::optional<std::uint32_t> action_requested_from_session_id_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
