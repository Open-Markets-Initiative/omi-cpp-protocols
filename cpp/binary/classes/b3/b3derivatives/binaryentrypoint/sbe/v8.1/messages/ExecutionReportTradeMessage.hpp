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
#include "../enums/AggressorIndicator.hpp"
#include "../enums/CrossPrioritization.hpp"
#include "../enums/CrossType.hpp"
#include "../enums/CrossedIndicator.hpp"
#include "../enums/ExecType.hpp"
#include "../enums/MultiLegReportingType.hpp"
#include "../enums/OrdStatus.hpp"
#include "../enums/OrderCategory.hpp"
#include "../enums/SecurityTradingStatus.hpp"
#include "../enums/Side.hpp"
#include "../enums/TradingSessionId.hpp"
#include "../enums/TradingSessionSubId.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/OutboundBusinessHeader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

class Visitor;

// ExecutionReport_TradeMessage
class ExecutionReportTradeMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionReportTradeMessage;

    ExecutionReportTradeMessage() = default;
    ExecutionReportTradeMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::optional<std::uint64_t> clordid_optional, std::uint64_t secondary_order_id, std::uint64_t security_id, std::optional<std::uint32_t> account, std::uint64_t last_qty, Decimal last_px, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::uint64_t leaves_qty, std::uint64_t cum_qty, AggressorIndicator aggressor_indicator, ExecType exec_type, OrderCategory order_category, MultiLegReportingType multi_leg_reporting_type, std::uint32_t trade_id, std::uint32_t contra_broker, std::uint64_t order_id, std::uint16_t trade_date, std::optional<std::uint8_t> tot_no_related_sym, const std::array<std::byte, 1>& offset_119_padding_1, std::optional<std::uint64_t> secondary_exec_id, std::optional<std::uint64_t> exec_ref_id, std::optional<std::uint64_t> crossid_optional, std::optional<CrossedIndicator> crossed_indicator, std::uint64_t order_qty, std::optional<TradingSessionId> trading_session_id, std::optional<TradingSessionSubId> trading_session_sub_id, std::optional<SecurityTradingStatus> security_trading_status, std::optional<CrossType> cross_type, std::optional<CrossPrioritization> cross_prioritization, const std::array<std::byte, 1>& offset_159_padding_1, std::optional<std::int32_t> strategy_id, const DeskId& desk_id, const Memo& memo);

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

    // ClOrdId Optional: clOrdID
    std::optional<std::uint64_t> clordid_optional() const;
    void set_clordid_optional(std::optional<std::uint64_t> value);

    // Secondary Order Id: secondaryOrderID
    std::uint64_t secondary_order_id() const;
    void set_secondary_order_id(std::uint64_t value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Last Qty: lastQty
    std::uint64_t last_qty() const;
    void set_last_qty(std::uint64_t value);

    // Last Px: lastPx
    Decimal last_px() const;
    void set_last_px(Decimal value);

    // Exec Id: execID
    std::uint64_t exec_id() const;
    void set_exec_id(std::uint64_t value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Leaves Qty: leavesQty
    std::uint64_t leaves_qty() const;
    void set_leaves_qty(std::uint64_t value);

    // Cum Qty: cumQty
    std::uint64_t cum_qty() const;
    void set_cum_qty(std::uint64_t value);

    // Aggressor Indicator: aggressorIndicator
    AggressorIndicator aggressor_indicator() const;
    void set_aggressor_indicator(AggressorIndicator value);

    // Exec Type: execType
    ExecType exec_type() const;
    void set_exec_type(ExecType value);

    // Order Category: orderCategory
    OrderCategory order_category() const;
    void set_order_category(OrderCategory value);

    // Multi Leg Reporting Type: multiLegReportingType
    MultiLegReportingType multi_leg_reporting_type() const;
    void set_multi_leg_reporting_type(MultiLegReportingType value);

    // Trade Id: tradeID
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Contra Broker: contraBroker
    std::uint32_t contra_broker() const;
    void set_contra_broker(std::uint32_t value);

    // Order Id: orderID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tot No Related Sym: totNoRelatedSym
    std::optional<std::uint8_t> tot_no_related_sym() const;
    void set_tot_no_related_sym(std::optional<std::uint8_t> value);

    // Offset 119 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_119_padding_1() const;
    std::array<std::byte, 1>& offset_119_padding_1();
    void set_offset_119_padding_1(const std::array<std::byte, 1>& value);

    // Secondary Exec Id: secondaryExecID
    std::optional<std::uint64_t> secondary_exec_id() const;
    void set_secondary_exec_id(std::optional<std::uint64_t> value);

    // Exec Ref Id: execRefID
    std::optional<std::uint64_t> exec_ref_id() const;
    void set_exec_ref_id(std::optional<std::uint64_t> value);

    // CrossId Optional: crossID
    std::optional<std::uint64_t> crossid_optional() const;
    void set_crossid_optional(std::optional<std::uint64_t> value);

    // Crossed Indicator: crossedIndicator
    std::optional<CrossedIndicator> crossed_indicator() const;
    void set_crossed_indicator(std::optional<CrossedIndicator> value);

    // Order Qty: orderQty
    std::uint64_t order_qty() const;
    void set_order_qty(std::uint64_t value);

    // Trading Session Id: tradingSessionID
    std::optional<TradingSessionId> trading_session_id() const;
    void set_trading_session_id(std::optional<TradingSessionId> value);

    // Trading Session Sub Id: tradingSessionSubID
    std::optional<TradingSessionSubId> trading_session_sub_id() const;
    void set_trading_session_sub_id(std::optional<TradingSessionSubId> value);

    // Security Trading Status: securityTradingStatus
    std::optional<SecurityTradingStatus> security_trading_status() const;
    void set_security_trading_status(std::optional<SecurityTradingStatus> value);

    // Cross Type: crossType
    std::optional<CrossType> cross_type() const;
    void set_cross_type(std::optional<CrossType> value);

    // Cross Prioritization: crossPrioritization
    std::optional<CrossPrioritization> cross_prioritization() const;
    void set_cross_prioritization(std::optional<CrossPrioritization> value);

    // Offset 159 Padding 1: 1 bytes padding
    const std::array<std::byte, 1>& offset_159_padding_1() const;
    std::array<std::byte, 1>& offset_159_padding_1();
    void set_offset_159_padding_1(const std::array<std::byte, 1>& value);

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

    bool operator==(const ExecutionReportTradeMessage& other) const;
    bool operator!=(const ExecutionReportTradeMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    Side side_{};
    OrdStatus ord_status_{};
    std::optional<std::uint64_t> clordid_optional_{};
    std::uint64_t secondary_order_id_{};
    std::uint64_t security_id_{};
    std::optional<std::uint32_t> account_{};
    std::uint64_t last_qty_{};
    Decimal last_px_{ 0, -4 };
    std::uint64_t exec_id_{};
    std::chrono::nanoseconds transact_time_{};
    std::uint64_t leaves_qty_{};
    std::uint64_t cum_qty_{};
    AggressorIndicator aggressor_indicator_{};
    ExecType exec_type_{};
    OrderCategory order_category_{};
    MultiLegReportingType multi_leg_reporting_type_{};
    std::uint32_t trade_id_{};
    std::uint32_t contra_broker_{};
    std::uint64_t order_id_{};
    std::uint16_t trade_date_{};
    std::optional<std::uint8_t> tot_no_related_sym_{};
    std::array<std::byte, 1> offset_119_padding_1_{};
    std::optional<std::uint64_t> secondary_exec_id_{};
    std::optional<std::uint64_t> exec_ref_id_{};
    std::optional<std::uint64_t> crossid_optional_{};
    std::optional<CrossedIndicator> crossed_indicator_{};
    std::uint64_t order_qty_{};
    std::optional<TradingSessionId> trading_session_id_{};
    std::optional<TradingSessionSubId> trading_session_sub_id_{};
    std::optional<SecurityTradingStatus> security_trading_status_{};
    std::optional<CrossType> cross_type_{};
    std::optional<CrossPrioritization> cross_prioritization_{};
    std::array<std::byte, 1> offset_159_padding_1_{};
    std::optional<std::int32_t> strategy_id_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
