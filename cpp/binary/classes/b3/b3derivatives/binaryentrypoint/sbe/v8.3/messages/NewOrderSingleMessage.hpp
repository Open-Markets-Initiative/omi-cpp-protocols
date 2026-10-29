#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/MmProtectionReset.hpp"
#include "../enums/Ordtype.hpp"
#include "../enums/RoutingInstruction.hpp"
#include "../enums/SelfTradePreventionInstruction.hpp"
#include "../enums/Side.hpp"
#include "../enums/TimeInForce.hpp"
#include "../messages/Message.hpp"
#include "../structs/CustodianInfo.hpp"
#include "../structs/DeskId.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../structs/InvestorId.hpp"
#include "../structs/Memo.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

class Visitor;

// NewOrderSingleMessage
class NewOrderSingleMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::NewOrderSingleMessage;

    NewOrderSingleMessage() = default;
    NewOrderSingleMessage(const InboundBusinessHeader& inbound_business_header, std::optional<std::uint8_t> ordtagid, MmProtectionReset mm_protection_reset, std::uint64_t clordid, std::optional<std::uint32_t> account, const std::string& sender_location, const std::string& entering_trader, SelfTradePreventionInstruction self_trade_prevention_instruction, std::uint64_t security_id, Side side, Ordtype ordtype, TimeInForce time_in_force, std::optional<RoutingInstruction> routing_instruction, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, const std::string& executing_trader_optional, std::optional<std::uint16_t> expire_date, const CustodianInfo& custodian_info, const InvestorId& investor_id, std::optional<std::int32_t> strategy_id, std::optional<std::uint32_t> trading_sub_account, const DeskId& desk_id, const Memo& memo);

    // Inbound Business Header: InboundBusinessHeader
    const InboundBusinessHeader& inbound_business_header() const;
    InboundBusinessHeader& inbound_business_header();
    void set_inbound_business_header(const InboundBusinessHeader& value);

    // OrdTagId: ordTagID
    std::optional<std::uint8_t> ordtagid() const;
    void set_ordtagid(std::optional<std::uint8_t> value);

    // Mm Protection Reset: mmProtectionReset
    MmProtectionReset mm_protection_reset() const;
    void set_mm_protection_reset(MmProtectionReset value);

    // ClOrdId: clOrdID
    std::uint64_t clordid() const;
    void set_clordid(std::uint64_t value);

    // Account: account
    std::optional<std::uint32_t> account() const;
    void set_account(std::optional<std::uint32_t> value);

    // Sender Location: senderLocation
    const std::string& sender_location() const;
    std::string& sender_location();
    void set_sender_location(const std::string& value);

    // Entering Trader: enteringTrader
    const std::string& entering_trader() const;
    std::string& entering_trader();
    void set_entering_trader(const std::string& value);

    // Self Trade Prevention Instruction: selfTradePreventionInstruction
    SelfTradePreventionInstruction self_trade_prevention_instruction() const;
    void set_self_trade_prevention_instruction(SelfTradePreventionInstruction value);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Side: side
    Side side() const;
    void set_side(Side value);

    // OrdType: ordType
    Ordtype ordtype() const;
    void set_ordtype(Ordtype value);

    // Time In Force: timeInForce
    TimeInForce time_in_force() const;
    void set_time_in_force(TimeInForce value);

    // Routing Instruction: routingInstruction
    std::optional<RoutingInstruction> routing_instruction() const;
    void set_routing_instruction(std::optional<RoutingInstruction> value);

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

    // Executing Trader Optional: executingTrader
    const std::string& executing_trader_optional() const;
    std::string& executing_trader_optional();
    void set_executing_trader_optional(const std::string& value);

    // Expire Date: expireDate
    std::optional<std::uint16_t> expire_date() const;
    void set_expire_date(std::optional<std::uint16_t> value);

    // Custodian Info: NewOrderSingleMessage
    const CustodianInfo& custodian_info() const;
    CustodianInfo& custodian_info();
    void set_custodian_info(const CustodianInfo& value);

    // Investor Id: SimpleNewOrderMessage
    const InvestorId& investor_id() const;
    InvestorId& investor_id();
    void set_investor_id(const InvestorId& value);

    // Strategy Id: strategyID
    std::optional<std::int32_t> strategy_id() const;
    void set_strategy_id(std::optional<std::int32_t> value);

    // Trading Sub Account: tradingSubAccount
    std::optional<std::uint32_t> trading_sub_account() const;
    void set_trading_sub_account(std::optional<std::uint32_t> value);

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

    bool operator==(const NewOrderSingleMessage& other) const;
    bool operator!=(const NewOrderSingleMessage& other) const;

  private:
    InboundBusinessHeader inbound_business_header_{};
    std::optional<std::uint8_t> ordtagid_{};
    MmProtectionReset mm_protection_reset_{};
    std::uint64_t clordid_{};
    std::optional<std::uint32_t> account_{};
    std::string sender_location_{};
    std::string entering_trader_{};
    SelfTradePreventionInstruction self_trade_prevention_instruction_{};
    std::uint64_t security_id_{};
    Side side_{};
    Ordtype ordtype_{};
    TimeInForce time_in_force_{};
    std::optional<RoutingInstruction> routing_instruction_{};
    std::uint64_t order_qty_{};
    std::optional<Decimal> price_optional_{};
    std::optional<Decimal> stop_px_{};
    std::optional<std::uint64_t> min_qty_{};
    std::optional<std::uint64_t> max_floor_{};
    std::string executing_trader_optional_{};
    std::optional<std::uint16_t> expire_date_{};
    CustodianInfo custodian_info_{};
    InvestorId investor_id_{};
    std::optional<std::int32_t> strategy_id_{};
    std::optional<std::uint32_t> trading_sub_account_{};
    DeskId desk_id_{};
    Memo memo_{};
};

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
