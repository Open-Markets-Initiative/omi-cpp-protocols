#include "SimpleNewOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

SimpleNewOrderMessage::SimpleNewOrderMessage(const InboundBusinessHeader& inbound_business_header, std::optional<std::uint8_t> ordtagid, MmProtectionReset mm_protection_reset, std::uint64_t clordid, std::optional<std::uint32_t> account, const std::string& sender_location, const std::string& entering_trader, SelfTradePreventionInstruction self_trade_prevention_instruction, std::uint64_t security_id, Side side, SimpleOrdtype simple_ordtype, TimeInForceSimple time_in_force_simple, std::optional<RoutingInstruction> routing_instruction, std::uint64_t order_qty, std::optional<Decimal> price_optional, const InvestorId& investor_id, const Memo& memo)
  : inbound_business_header_(inbound_business_header), ordtagid_(ordtagid), mm_protection_reset_(mm_protection_reset), clordid_(clordid), account_(account), sender_location_(sender_location), entering_trader_(entering_trader), self_trade_prevention_instruction_(self_trade_prevention_instruction), security_id_(security_id), side_(side), simple_ordtype_(simple_ordtype), time_in_force_simple_(time_in_force_simple), routing_instruction_(routing_instruction), order_qty_(order_qty), price_optional_(price_optional), investor_id_(investor_id), memo_(memo) {}

const InboundBusinessHeader& SimpleNewOrderMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& SimpleNewOrderMessage::inbound_business_header() { return inbound_business_header_; }
void SimpleNewOrderMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

std::optional<std::uint8_t> SimpleNewOrderMessage::ordtagid() const { return ordtagid_; }
void SimpleNewOrderMessage::set_ordtagid(std::optional<std::uint8_t> value) { ordtagid_ = value; }

MmProtectionReset SimpleNewOrderMessage::mm_protection_reset() const { return mm_protection_reset_; }
void SimpleNewOrderMessage::set_mm_protection_reset(MmProtectionReset value) { mm_protection_reset_ = value; }

std::uint64_t SimpleNewOrderMessage::clordid() const { return clordid_; }
void SimpleNewOrderMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::optional<std::uint32_t> SimpleNewOrderMessage::account() const { return account_; }
void SimpleNewOrderMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

const std::string& SimpleNewOrderMessage::sender_location() const { return sender_location_; }
std::string& SimpleNewOrderMessage::sender_location() { return sender_location_; }
void SimpleNewOrderMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& SimpleNewOrderMessage::entering_trader() const { return entering_trader_; }
std::string& SimpleNewOrderMessage::entering_trader() { return entering_trader_; }
void SimpleNewOrderMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

SelfTradePreventionInstruction SimpleNewOrderMessage::self_trade_prevention_instruction() const { return self_trade_prevention_instruction_; }
void SimpleNewOrderMessage::set_self_trade_prevention_instruction(SelfTradePreventionInstruction value) { self_trade_prevention_instruction_ = value; }

std::uint64_t SimpleNewOrderMessage::security_id() const { return security_id_; }
void SimpleNewOrderMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

Side SimpleNewOrderMessage::side() const { return side_; }
void SimpleNewOrderMessage::set_side(Side value) { side_ = value; }

SimpleOrdtype SimpleNewOrderMessage::simple_ordtype() const { return simple_ordtype_; }
void SimpleNewOrderMessage::set_simple_ordtype(SimpleOrdtype value) { simple_ordtype_ = value; }

TimeInForceSimple SimpleNewOrderMessage::time_in_force_simple() const { return time_in_force_simple_; }
void SimpleNewOrderMessage::set_time_in_force_simple(TimeInForceSimple value) { time_in_force_simple_ = value; }

std::optional<RoutingInstruction> SimpleNewOrderMessage::routing_instruction() const { return routing_instruction_; }
void SimpleNewOrderMessage::set_routing_instruction(std::optional<RoutingInstruction> value) { routing_instruction_ = value; }

std::uint64_t SimpleNewOrderMessage::order_qty() const { return order_qty_; }
void SimpleNewOrderMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<Decimal> SimpleNewOrderMessage::price_optional() const { return price_optional_; }
void SimpleNewOrderMessage::set_price_optional(std::optional<Decimal> value) { price_optional_ = value; }

const InvestorId& SimpleNewOrderMessage::investor_id() const { return investor_id_; }
InvestorId& SimpleNewOrderMessage::investor_id() { return investor_id_; }
void SimpleNewOrderMessage::set_investor_id(const InvestorId& value) { investor_id_ = value; }

const Memo& SimpleNewOrderMessage::memo() const { return memo_; }
Memo& SimpleNewOrderMessage::memo() { return memo_; }
void SimpleNewOrderMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode SimpleNewOrderMessage::type() const { return message_type; }

std::string_view SimpleNewOrderMessage::name() const { return "Simple New Order Message"; }

std::size_t SimpleNewOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += inbound_business_header_.decode(data + offset, length - offset);

    wire::require("SimpleNewOrderMessage", offset + 1, length);
    ordtagid_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("SimpleNewOrderMessage", offset + 1, length);
    mm_protection_reset_ = static_cast<MmProtectionReset>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("SimpleNewOrderMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("SimpleNewOrderMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("SimpleNewOrderMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("SimpleNewOrderMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("SimpleNewOrderMessage", offset + 1, length);
    self_trade_prevention_instruction_ = static_cast<SelfTradePreventionInstruction>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("SimpleNewOrderMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("SimpleNewOrderMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("SimpleNewOrderMessage", offset + 1, length);
    simple_ordtype_ = static_cast<SimpleOrdtype>(wire::read_char(data + offset));
    offset += 1;

    wire::require("SimpleNewOrderMessage", offset + 1, length);
    time_in_force_simple_ = static_cast<TimeInForceSimple>(wire::read_char(data + offset));
    offset += 1;

    wire::require("SimpleNewOrderMessage", offset + 1, length);
    routing_instruction_ = wire::nullable_enum<RoutingInstruction>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("SimpleNewOrderMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("SimpleNewOrderMessage", offset + 8, length);
    price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    offset += investor_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SimpleNewOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SimpleNewOrderMessage", encoded_size(), capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, ordtagid_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(mm_protection_reset_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(clordid_));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(self_trade_prevention_instruction_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(simple_ordtype_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(time_in_force_simple_));
    offset += 1;

    wire::write_u8(data + offset, routing_instruction_ ? static_cast<std::uint8_t>(*routing_instruction_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, price_optional_ ? static_cast<std::int64_t>(price_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    offset += investor_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SimpleNewOrderMessage::encoded_size() const {
    return inbound_business_header_.encoded_size() + 1 + 1 + 8 + 4 + 10 + 5 + 1 + 8 + 1 + 1 + 1 + 1 + 8 + 8 + investor_id_.encoded_size() + memo_.encoded_size();
}

void SimpleNewOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SimpleNewOrderMessage::clone() const {
    return std::make_unique<SimpleNewOrderMessage>(*this);
}

void SimpleNewOrderMessage::print(std::ostream& out) const {
    out << "SimpleNewOrderMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", ordtagid=";
    print::optional(out, ordtagid_);
    out << ", mm_protection_reset=";
    out << mm_protection_reset_;
    out << ", clordid=";
    out << clordid_;
    out << ", account=";
    print::optional(out, account_);
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", self_trade_prevention_instruction=";
    out << self_trade_prevention_instruction_;
    out << ", security_id=";
    out << security_id_;
    out << ", side=";
    out << side_;
    out << ", simple_ordtype=";
    out << simple_ordtype_;
    out << ", time_in_force_simple=";
    out << time_in_force_simple_;
    out << ", routing_instruction=";
    print::optional(out, routing_instruction_);
    out << ", order_qty=";
    out << order_qty_;
    out << ", price_optional=";
    print::optional(out, price_optional_);
    out << ", investor_id=";
    investor_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool SimpleNewOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SimpleNewOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SimpleNewOrderMessage::operator==(const SimpleNewOrderMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && ordtagid_ == other.ordtagid_
        && mm_protection_reset_ == other.mm_protection_reset_
        && clordid_ == other.clordid_
        && account_ == other.account_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && self_trade_prevention_instruction_ == other.self_trade_prevention_instruction_
        && security_id_ == other.security_id_
        && side_ == other.side_
        && simple_ordtype_ == other.simple_ordtype_
        && time_in_force_simple_ == other.time_in_force_simple_
        && routing_instruction_ == other.routing_instruction_
        && order_qty_ == other.order_qty_
        && price_optional_ == other.price_optional_
        && investor_id_ == other.investor_id_
        && memo_ == other.memo_;
}

bool SimpleNewOrderMessage::operator!=(const SimpleNewOrderMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
