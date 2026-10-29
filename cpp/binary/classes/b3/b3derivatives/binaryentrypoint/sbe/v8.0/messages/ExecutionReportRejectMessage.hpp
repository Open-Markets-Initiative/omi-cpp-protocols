#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/CrossedIndicator.hpp"
#include "../enums/CxlRejResponseTo.hpp"
#include "../enums/OrdRejReason.hpp"
#include "../enums/Ordtype.hpp"
#include "../enums/Side.hpp"
#include "../enums/TimeInForce.hpp"
#include "../messages/Message.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/Memo.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../structs/Text.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

class Visitor;

// ExecutionReport_RejectMessage
class ExecutionReportRejectMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::ExecutionReportRejectMessage;

    ExecutionReportRejectMessage() = default;
    ExecutionReportRejectMessage(const OutboundBusinessHeader& outbound_business_header, Side side, CxlRejResponseTo cxl_rej_response_to, std::uint64_t clordid, std::optional<std::uint64_t> secondary_order_id_optional, std::uint64_t security_id, OrdRejReason ord_rej_reason, std::chrono::nanoseconds transact_time, std::uint64_t exec_id, std::optional<std::uint64_t> order_id_optional, std::optional<std::uint64_t> origclordid, std::optional<std::uint32_t> account, Ordtype ordtype, TimeInForce time_in_force, std::optional<std::uint16_t> expire_date, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, std::optional<std::uint64_t> crossid_optional, std::optional<CrossedIndicator> crossed_indicator, const DeskId& desk_id, const Memo& memo, const Text& text);

    // Outbound Business Header: OutboundBusinessHeader
    const OutboundBusinessHeader& outbound_business_header() const;
    OutboundBusinessHeader& outbound_business_header();
    void set_outbound_business_header(const OutboundBusinessHeader& value);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // Cxl Rej Response To: cxlRejResponseTo
    CxlRejResponseTo cxl_rej_response_to() const;
    void set_cxl_rej_response_to(CxlRejResponseTo value);

    // ClOrdId: clOrdID
    std::uint64_t clordid() const;
    void set_clordid(std::uint64_t value);

    // Secondary Order Id Optional: secondaryOrderID
    std::optional<std::uint64_t> secondary_order_id_optional() const;
    void set_secondary_order_id_optional(std::optional<std::uint64_t> value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Ord Rej Reason: ordRejReason
    OrdRejReason ord_rej_reason() const;
    void set_ord_rej_reason(OrdRejReason value);

    // Transact Time: transactTime
    std::chrono::nanoseconds transact_time() const;
    void set_transact_time(std::chrono::nanoseconds value);

    // Exec Id: execID
    std::uint64_t exec_id() const;
    void set_exec_id(std::uint64_t value);

    // Order Id Optional: orderID
    std::optional<std::uint64_t> order_id_optional() const;
    void set_order_id_optional(std::optional<std::uint64_t> value);

    // OrigClOrdId: origClOrdID
    std::optional<std::uint64_t> origclordid() const;
    void set_origclordid(std::optional<std::uint64_t> value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

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

    // Crossed Indicator: crossedIndicator
    std::optional<CrossedIndicator> crossed_indicator() const;
    void set_crossed_indicator(std::optional<CrossedIndicator> value);

    // Desk Id: deskID data struct
    const DeskId& desk_id() const;
    DeskId& desk_id();
    void set_desk_id(const DeskId& value);

    // Memo: memo data struct
    const Memo& memo() const;
    Memo& memo();
    void set_memo(const Memo& value);

    // Text: text data struct
    const Text& text() const;
    Text& text();
    void set_text(const Text& value);

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

    bool operator==(const ExecutionReportRejectMessage& other) const;
    bool operator!=(const ExecutionReportRejectMessage& other) const;

  private:
    OutboundBusinessHeader outbound_business_header_{};
    Side side_{};
    CxlRejResponseTo cxl_rej_response_to_{};
    std::uint64_t clordid_{};
    std::optional<std::uint64_t> secondary_order_id_optional_{};
    std::uint64_t security_id_{};
    OrdRejReason ord_rej_reason_{};
    std::chrono::nanoseconds transact_time_{};
    std::uint64_t exec_id_{};
    std::optional<std::uint64_t> order_id_optional_{};
    std::optional<std::uint64_t> origclordid_{};
    std::optional<std::uint32_t> account_{};
    Ordtype ordtype_{};
    TimeInForce time_in_force_{};
    std::optional<std::uint16_t> expire_date_{};
    std::uint64_t order_qty_{};
    std::optional<Decimal> price_optional_{};
    std::optional<Decimal> stop_px_{};
    std::optional<std::uint64_t> min_qty_{};
    std::optional<std::uint64_t> max_floor_{};
    std::optional<std::uint64_t> crossid_optional_{};
    std::optional<CrossedIndicator> crossed_indicator_{};
    DeskId desk_id_{};
    Memo memo_{};
    Text text_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
