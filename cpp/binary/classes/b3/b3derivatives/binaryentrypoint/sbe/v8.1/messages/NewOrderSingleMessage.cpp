#include "NewOrderSingleMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

NewOrderSingleMessage::NewOrderSingleMessage(const InboundBusinessHeader& inbound_business_header, std::optional<std::uint8_t> ordtagid, MmProtectionReset mm_protection_reset, std::uint64_t clordid, std::optional<std::uint32_t> account, const std::string& sender_location, const std::string& entering_trader, SelfTradePreventionInstruction self_trade_prevention_instruction, std::uint64_t security_id, Side side, Ordtype ordtype, TimeInForce time_in_force, std::optional<RoutingInstruction> routing_instruction, std::uint64_t order_qty, std::optional<Decimal> price_optional, std::optional<Decimal> stop_px, std::optional<std::uint64_t> min_qty, std::optional<std::uint64_t> max_floor, const std::string& executing_trader_optional, std::optional<std::uint16_t> expire_date, const CustodianInfo& custodian_info, const InvestorId& investor_id, std::optional<std::int32_t> strategy_id, const DeskId& desk_id, const Memo& memo)
  : inbound_business_header_(inbound_business_header), ordtagid_(ordtagid), mm_protection_reset_(mm_protection_reset), clordid_(clordid), account_(account), sender_location_(sender_location), entering_trader_(entering_trader), self_trade_prevention_instruction_(self_trade_prevention_instruction), security_id_(security_id), side_(side), ordtype_(ordtype), time_in_force_(time_in_force), routing_instruction_(routing_instruction), order_qty_(order_qty), price_optional_(price_optional), stop_px_(stop_px), min_qty_(min_qty), max_floor_(max_floor), executing_trader_optional_(executing_trader_optional), expire_date_(expire_date), custodian_info_(custodian_info), investor_id_(investor_id), strategy_id_(strategy_id), desk_id_(desk_id), memo_(memo) {}

const InboundBusinessHeader& NewOrderSingleMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& NewOrderSingleMessage::inbound_business_header() { return inbound_business_header_; }
void NewOrderSingleMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

std::optional<std::uint8_t> NewOrderSingleMessage::ordtagid() const { return ordtagid_; }
void NewOrderSingleMessage::set_ordtagid(std::optional<std::uint8_t> value) { ordtagid_ = value; }

MmProtectionReset NewOrderSingleMessage::mm_protection_reset() const { return mm_protection_reset_; }
void NewOrderSingleMessage::set_mm_protection_reset(MmProtectionReset value) { mm_protection_reset_ = value; }

std::uint64_t NewOrderSingleMessage::clordid() const { return clordid_; }
void NewOrderSingleMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::optional<std::uint32_t> NewOrderSingleMessage::account() const { return account_; }
void NewOrderSingleMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

const std::string& NewOrderSingleMessage::sender_location() const { return sender_location_; }
std::string& NewOrderSingleMessage::sender_location() { return sender_location_; }
void NewOrderSingleMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& NewOrderSingleMessage::entering_trader() const { return entering_trader_; }
std::string& NewOrderSingleMessage::entering_trader() { return entering_trader_; }
void NewOrderSingleMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

SelfTradePreventionInstruction NewOrderSingleMessage::self_trade_prevention_instruction() const { return self_trade_prevention_instruction_; }
void NewOrderSingleMessage::set_self_trade_prevention_instruction(SelfTradePreventionInstruction value) { self_trade_prevention_instruction_ = value; }

std::uint64_t NewOrderSingleMessage::security_id() const { return security_id_; }
void NewOrderSingleMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

Side NewOrderSingleMessage::side() const { return side_; }
void NewOrderSingleMessage::set_side(Side value) { side_ = value; }

Ordtype NewOrderSingleMessage::ordtype() const { return ordtype_; }
void NewOrderSingleMessage::set_ordtype(Ordtype value) { ordtype_ = value; }

TimeInForce NewOrderSingleMessage::time_in_force() const { return time_in_force_; }
void NewOrderSingleMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

std::optional<RoutingInstruction> NewOrderSingleMessage::routing_instruction() const { return routing_instruction_; }
void NewOrderSingleMessage::set_routing_instruction(std::optional<RoutingInstruction> value) { routing_instruction_ = value; }

std::uint64_t NewOrderSingleMessage::order_qty() const { return order_qty_; }
void NewOrderSingleMessage::set_order_qty(std::uint64_t value) { order_qty_ = value; }

std::optional<Decimal> NewOrderSingleMessage::price_optional() const { return price_optional_; }
void NewOrderSingleMessage::set_price_optional(std::optional<Decimal> value) { price_optional_ = value; }

std::optional<Decimal> NewOrderSingleMessage::stop_px() const { return stop_px_; }
void NewOrderSingleMessage::set_stop_px(std::optional<Decimal> value) { stop_px_ = value; }

std::optional<std::uint64_t> NewOrderSingleMessage::min_qty() const { return min_qty_; }
void NewOrderSingleMessage::set_min_qty(std::optional<std::uint64_t> value) { min_qty_ = value; }

std::optional<std::uint64_t> NewOrderSingleMessage::max_floor() const { return max_floor_; }
void NewOrderSingleMessage::set_max_floor(std::optional<std::uint64_t> value) { max_floor_ = value; }

const std::string& NewOrderSingleMessage::executing_trader_optional() const { return executing_trader_optional_; }
std::string& NewOrderSingleMessage::executing_trader_optional() { return executing_trader_optional_; }
void NewOrderSingleMessage::set_executing_trader_optional(const std::string& value) { executing_trader_optional_ = value; }

std::optional<std::uint16_t> NewOrderSingleMessage::expire_date() const { return expire_date_; }
void NewOrderSingleMessage::set_expire_date(std::optional<std::uint16_t> value) { expire_date_ = value; }

const CustodianInfo& NewOrderSingleMessage::custodian_info() const { return custodian_info_; }
CustodianInfo& NewOrderSingleMessage::custodian_info() { return custodian_info_; }
void NewOrderSingleMessage::set_custodian_info(const CustodianInfo& value) { custodian_info_ = value; }

const InvestorId& NewOrderSingleMessage::investor_id() const { return investor_id_; }
InvestorId& NewOrderSingleMessage::investor_id() { return investor_id_; }
void NewOrderSingleMessage::set_investor_id(const InvestorId& value) { investor_id_ = value; }

std::optional<std::int32_t> NewOrderSingleMessage::strategy_id() const { return strategy_id_; }
void NewOrderSingleMessage::set_strategy_id(std::optional<std::int32_t> value) { strategy_id_ = value; }

const DeskId& NewOrderSingleMessage::desk_id() const { return desk_id_; }
DeskId& NewOrderSingleMessage::desk_id() { return desk_id_; }
void NewOrderSingleMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& NewOrderSingleMessage::memo() const { return memo_; }
Memo& NewOrderSingleMessage::memo() { return memo_; }
void NewOrderSingleMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode NewOrderSingleMessage::type() const { return message_type; }

std::string_view NewOrderSingleMessage::name() const { return "New Order Single Message"; }

std::size_t NewOrderSingleMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += inbound_business_header_.decode(data + offset, length - offset);

    wire::require("NewOrderSingleMessage", offset + 1, length);
    ordtagid_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("NewOrderSingleMessage", offset + 1, length);
    mm_protection_reset_ = static_cast<MmProtectionReset>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("NewOrderSingleMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("NewOrderSingleMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("NewOrderSingleMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("NewOrderSingleMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("NewOrderSingleMessage", offset + 1, length);
    self_trade_prevention_instruction_ = static_cast<SelfTradePreventionInstruction>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("NewOrderSingleMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("NewOrderSingleMessage", offset + 1, length);
    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::require("NewOrderSingleMessage", offset + 1, length);
    ordtype_ = static_cast<Ordtype>(wire::read_char(data + offset));
    offset += 1;

    wire::require("NewOrderSingleMessage", offset + 1, length);
    time_in_force_ = static_cast<TimeInForce>(wire::read_char(data + offset));
    offset += 1;

    wire::require("NewOrderSingleMessage", offset + 1, length);
    routing_instruction_ = wire::nullable_enum<RoutingInstruction>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("NewOrderSingleMessage", offset + 8, length);
    order_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("NewOrderSingleMessage", offset + 8, length);
    price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("NewOrderSingleMessage", offset + 8, length);
    stop_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("NewOrderSingleMessage", offset + 8, length);
    min_qty_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("NewOrderSingleMessage", offset + 8, length);
    max_floor_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("NewOrderSingleMessage", offset + 5, length);
    executing_trader_optional_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("NewOrderSingleMessage", offset + 2, length);
    expire_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    offset += custodian_info_.decode(data + offset, length - offset);

    offset += investor_id_.decode(data + offset, length - offset);

    wire::require("NewOrderSingleMessage", offset + 4, length);
    strategy_id_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t NewOrderSingleMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NewOrderSingleMessage", encoded_size(), capacity);

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

    wire::write_char(data + offset, static_cast<char>(ordtype_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(time_in_force_));
    offset += 1;

    wire::write_u8(data + offset, routing_instruction_ ? static_cast<std::uint8_t>(*routing_instruction_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_qty_));
    offset += 8;

    wire::write_i64_le(data + offset, price_optional_ ? static_cast<std::int64_t>(price_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, stop_px_ ? static_cast<std::int64_t>(stop_px_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u64_le(data + offset, min_qty_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, max_floor_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_text(data + offset, 5, '\0', executing_trader_optional_);
    offset += 5;

    wire::write_u16_le(data + offset, expire_date_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    offset += custodian_info_.encode(data + offset, capacity - offset);

    offset += investor_id_.encode(data + offset, capacity - offset);

    wire::write_i32_le(data + offset, strategy_id_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t NewOrderSingleMessage::encoded_size() const {
    return inbound_business_header_.encoded_size() + 1 + 1 + 8 + 4 + 10 + 5 + 1 + 8 + 1 + 1 + 1 + 1 + 8 + 8 + 8 + 8 + 8 + 5 + 2 + custodian_info_.encoded_size() + investor_id_.encoded_size() + 4 + desk_id_.encoded_size() + memo_.encoded_size();
}

void NewOrderSingleMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NewOrderSingleMessage::clone() const {
    return std::make_unique<NewOrderSingleMessage>(*this);
}

void NewOrderSingleMessage::print(std::ostream& out) const {
    out << "NewOrderSingleMessage{";
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
    out << ", ordtype=";
    out << ordtype_;
    out << ", time_in_force=";
    out << time_in_force_;
    out << ", routing_instruction=";
    print::optional(out, routing_instruction_);
    out << ", order_qty=";
    out << order_qty_;
    out << ", price_optional=";
    print::optional(out, price_optional_);
    out << ", stop_px=";
    print::optional(out, stop_px_);
    out << ", min_qty=";
    print::optional(out, min_qty_);
    out << ", max_floor=";
    print::optional(out, max_floor_);
    out << ", executing_trader_optional=";
    print::text(out, executing_trader_optional_);
    out << ", expire_date=";
    print::optional(out, expire_date_);
    out << ", custodian_info=";
    custodian_info_.print(out);
    out << ", investor_id=";
    investor_id_.print(out);
    out << ", strategy_id=";
    print::optional(out, strategy_id_);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool NewOrderSingleMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NewOrderSingleMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NewOrderSingleMessage::operator==(const NewOrderSingleMessage& other) const {
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
        && ordtype_ == other.ordtype_
        && time_in_force_ == other.time_in_force_
        && routing_instruction_ == other.routing_instruction_
        && order_qty_ == other.order_qty_
        && price_optional_ == other.price_optional_
        && stop_px_ == other.stop_px_
        && min_qty_ == other.min_qty_
        && max_floor_ == other.max_floor_
        && executing_trader_optional_ == other.executing_trader_optional_
        && expire_date_ == other.expire_date_
        && custodian_info_ == other.custodian_info_
        && investor_id_ == other.investor_id_
        && strategy_id_ == other.strategy_id_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool NewOrderSingleMessage::operator!=(const NewOrderSingleMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
