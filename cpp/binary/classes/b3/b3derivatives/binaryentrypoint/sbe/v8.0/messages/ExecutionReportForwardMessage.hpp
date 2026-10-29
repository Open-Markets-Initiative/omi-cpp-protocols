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
#include "../enums/OrdStatus.hpp"
#include "../enums/SettlTypeOptional.hpp"
#include "../enums/Side.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/OutboundBusinessHeader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// ExecutionReport_ForwardMessage
class ExecutionReportForwardMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionReportForwardMessage;

    ExecutionReportForwardMessage() = default;
    ExecutionReportForwardMessage(const OutboundBusinessHeader& outbound_business_header, Side side, OrdStatus ord_status, std::optional<std::uint64_t> clordid_optional, std::uint64_t secondary_order_id, std::uint64_t security_id, std::optional<std::uint32_t> account, std::uint64_t last_qty, Decimal last_px, std::uint64_t exec_id, std::chrono::nanoseconds transact_time, std::uint64_t leaves_qty, std::uint64_t cum_qty, std::uint32_t trade_id, std::uint32_t contra_broker, std::uint64_t order_id, AggressorIndicator aggressor_indicator, SettlTypeOptional settl_type_optional, std::uint16_t trade_date, std::optional<std::uint16_t> days_to_settlement_optional, const std::array<std::byte, 2>& offset_118_padding_2, std::optional<std::uint64_t> secondary_exec_id, std::optional<std::uint64_t> exec_ref_id, std::optional<Decimal> fixed_rate_optional, std::uint64_t order_qty, const DeskId& desk_id, const Memo& memo);

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

    // Trade Id: tradeID
    std::uint32_t trade_id() const;
    void set_trade_id(std::uint32_t value);

    // Contra Broker: contraBroker
    std::uint32_t contra_broker() const;
    void set_contra_broker(std::uint32_t value);

    // Order Id: orderID
    std::uint64_t order_id() const;
    void set_order_id(std::uint64_t value);

    // Aggressor Indicator: aggressorIndicator
    AggressorIndicator aggressor_indicator() const;
    void set_aggressor_indicator(AggressorIndicator value);

    // Settl Type Optional: settlType
    SettlTypeOptional settl_type_optional() const;
    void set_settl_type_optional(SettlTypeOptional value);

    // Trade Date: tradeDate
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Days To Settlement Optional: daysToSettlement
    std::optional<std::uint16_t> days_to_settlement_optional() const;
    void set_days_to_settlement_optional(std::optional<std::uint16_t> value);

    // Offset 118 Padding 2: 2 bytes padding
    const std::array<std::byte, 2>& offset_118_padding_2() const;
    std::array<std::byte, 2>& offset_118_padding_2();
    void set_offset_118_padding_2(const std::array<std::byte, 2>& value);

    // Secondary Exec Id: secondaryExecID
    std::optional<std::uint64_t> secondary_exec_id() const;
    void set_secondary_exec_id(std::optional<std::uint64_t> value);

    // Exec Ref Id: execRefID
    std::optional<std::uint64_t> exec_ref_id() const;
    void set_exec_ref_id(std::optional<std::uint64_t> value);

    // Fixed Rate Optional: fixedRate
    std::optional<Decimal> fixed_rate_optional() const;
    void set_fixed_rate_optional(std::optional<Decimal> value);

    // Order Qty: orderQty
    std::uint64_t order_qty() const;
    void set_order_qty(std::uint64_t value);

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

    bool operator==(const ExecutionReportForwardMessage& other) const;
    bool operator!=(const ExecutionReportForwardMessage& other) const;

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
    std::uint32_t trade_id_{};
    std::uint32_t contra_broker_{};
    std::uint64_t order_id_{};
    AggressorIndicator aggressor_indicator_{};
    SettlTypeOptional settl_type_optional_{};
    std::uint16_t trade_date_{};
    std::optional<std::uint16_t> days_to_settlement_optional_{};
    std::array<std::byte, 2> offset_118_padding_2_{};
    std::optional<std::uint64_t> secondary_exec_id_{};
    std::optional<std::uint64_t> exec_ref_id_{};
    std::optional<Decimal> fixed_rate_optional_{};
    std::uint64_t order_qty_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
