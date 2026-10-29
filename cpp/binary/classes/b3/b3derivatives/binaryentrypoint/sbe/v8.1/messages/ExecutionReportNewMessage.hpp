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
#include "../enums/CrossPrioritization.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/MmProtectionResetOptional.hpp"
#include "../enums/MultiLegReportingType.hpp"
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

// ExecutionReport_NewMessage
class ExecutionReportNewMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionReportNewMessage;

    ExecutionReportNewMessage() = default;
    ExecutionReportNewMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::uint64_t clordid, std::uint64_t secondary_order_id, std::uint64_t security_id, std::uint64_t order_id, std::optional<std::uint32_t> account, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::optional<std::chrono::nanoseconds> market_segment_received_time, std::optional<Decimal> protection_price, std::uint16_t trade_date, WorkingIndicator working_indicator, MultiLegReportingType multi_leg_reporting_type, Ordtype ordtype, TimeInForce time_in_force, std::optional<std::uint16_t> expire_date, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, std::optional<std::uint64_t> crossid_optional, std::optional<std::chrono::nanoseconds> received_time, const std::array<std::byte, 3>& offset_152_padding_3, std::optional<std::uint8_t> ordtagid, const InvestorId& investor_id, std::optional<CrossType> cross_type, std::optional<CrossPrioritization> cross_prioritization, std::optional<MmProtectionResetOptional> mm_protection_reset_optional, const std::array<std::byte, 1>& offset_167_padding_1, std::optional<std::int32_t> strategy_id, const DeskId& desk_id, const Memo& memo);

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

    // Order Id: orderID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

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

    // Protection Price: protectionPrice
    std::optional<Decimal> protection_price() const;
    void set_protection_price(std::optional<Decimal> value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Working Indicator: workingIndicator
    WorkingIndicator working_indicator() const;
    void set_working_indicator(WorkingIndicator value);

    // Multi Leg Reporting Type: multiLegReportingType
    MultiLegReportingType multi_leg_reporting_type() const;
    void set_multi_leg_reporting_type(MultiLegReportingType value);

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

    // CrossId Optional: crossID
    std::optional<std::uint64_t> crossid_optional() const;
    void set_crossid_optional(std::optional<std::uint64_t> value);

    // Received Time: receivedTime
    std::optional<std::chrono::nanoseconds> received_time() const;
    void set_received_time(std::optional<std::chrono::nanoseconds> value);

    // Offset 152 Padding 3: 3 bytes padding
    const std::array<std::byte, 3>& offset_152_padding_3() const;
    std::array<std::byte, 3>& offset_152_padding_3();
    void set_offset_152_padding_3(const std::array<std::byte, 3>& value);

    // OrdTagId: ordTagID
    std::optional<std::uint8_t> ordtagid() const;
    void set_ordtagid(std::optional<std::uint8_t> value);

    // Investor Id: SimpleNewOrderMessage
    const InvestorId& investor_id() const;
    InvestorId& investor_id();
    void set_investor_id(const InvestorId& value);

    // Cross Type: crossType
    std::optional<CrossType> cross_type() const;
    void set_cross_type(std::optional<CrossType> value);

    // Cross Prioritization: crossPrioritization
    std::optional<CrossPrioritization> cross_prioritization() const;
    void set_cross_prioritization(std::optional<CrossPrioritization> value);

    // Mm Protection Reset Optional: mmProtectionReset
    std::optional<MmProtectionResetOptional> mm_protection_reset_optional() const;
    void set_mm_protection_reset_optional(std::optional<MmProtectionResetOptional> value);

    // Offset 167 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_167_padding_1() const;
    std::array<std::byte, 1>& offset_167_padding_1();
    void set_offset_167_padding_1(const std::array<std::byte, 1>& value);

    // Strategy Id: strategyID
    std::optional<std::int32_t> strategy_id() const;
    void set_strategy_id(std::optional<std::int32_t> value);

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

    bool operator==(const ExecutionReportNewMessage& other) const;
    bool operator!=(const ExecutionReportNewMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    Side side_{};
    OrdStatus ord_status_{};
    std::uint64_t clordid_{};
    std::uint64_t secondary_order_id_{};
    std::uint64_t security_id_{};
    std::uint64_t order_id_{};
    std::optional<std::uint32_t> account_{};
    std::uint64_t exec_id_{};
    std::chrono::nanoseconds transact_time_{};
    std::optional<std::chrono::nanoseconds> market_segment_received_time_{};
    std::optional<Decimal> protection_price_{};
    std::uint16_t trade_date_{};
    WorkingIndicator working_indicator_{};
    MultiLegReportingType multi_leg_reporting_type_{};
    Ordtype ordtype_{};
    TimeInForce time_in_force_{};
    std::optional<std::uint16_t> expire_date_{};
    std::uint64_t order_qty_{};
    std::optional<Decimal> price_optional_{};
    std::optional<Decimal> stop_px_{};
    std::optional<std::uint64_t> min_qty_{};
    std::optional<std::uint64_t> max_floor_{};
    std::optional<std::uint64_t> crossid_optional_{};
    std::optional<std::chrono::nanoseconds> received_time_{};
    std::array<std::byte, 3> offset_152_padding_3_{};
    std::optional<std::uint8_t> ordtagid_{};
    InvestorId investor_id_{};
    std::optional<CrossType> cross_type_{};
    std::optional<CrossPrioritization> cross_prioritization_{};
    std::optional<MmProtectionResetOptional> mm_protection_reset_optional_{};
    std::array<std::byte, 1> offset_167_padding_1_{};
    std::optional<std::int32_t> strategy_id_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
