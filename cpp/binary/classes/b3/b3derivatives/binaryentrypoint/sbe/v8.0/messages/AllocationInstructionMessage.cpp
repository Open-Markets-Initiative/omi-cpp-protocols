#include "AllocationInstructionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

AllocationInstructionMessage::AllocationInstructionMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t alloc_id, std::uint64_t security_id, AllocTransType alloc_trans_type, AllocType alloc_type, AllocNoOrdersType alloc_no_orders_type, std::uint64_t quantity, const std::string& sender_location, const std::string& entering_trader, std::uint32_t trade_id, std::optional<std::uint16_t> trade_date_optional, std::uint64_t individual_alloc_id, std::uint32_t alloc_account, std::uint64_t alloc_qty, const DeskId& desk_id, const Memo& memo)
  : inbound_business_header_(inbound_business_header), alloc_id_(alloc_id), security_id_(security_id), alloc_trans_type_(alloc_trans_type), alloc_type_(alloc_type), alloc_no_orders_type_(alloc_no_orders_type), quantity_(quantity), sender_location_(sender_location), entering_trader_(entering_trader), trade_id_(trade_id), trade_date_optional_(trade_date_optional), individual_alloc_id_(individual_alloc_id), alloc_account_(alloc_account), alloc_qty_(alloc_qty), desk_id_(desk_id), memo_(memo) {}

const InboundBusinessHeader& AllocationInstructionMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& AllocationInstructionMessage::inbound_business_header() { return inbound_business_header_; }
void AllocationInstructionMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

std::uint64_t AllocationInstructionMessage::alloc_id() const { return alloc_id_; }
void AllocationInstructionMessage::set_alloc_id(std::uint64_t value) { alloc_id_ = value; }

std::uint64_t AllocationInstructionMessage::security_id() const { return security_id_; }
void AllocationInstructionMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

AllocTransType AllocationInstructionMessage::alloc_trans_type() const { return alloc_trans_type_; }
void AllocationInstructionMessage::set_alloc_trans_type(AllocTransType value) { alloc_trans_type_ = value; }

AllocType AllocationInstructionMessage::alloc_type() const { return alloc_type_; }
void AllocationInstructionMessage::set_alloc_type(AllocType value) { alloc_type_ = value; }

AllocNoOrdersType AllocationInstructionMessage::alloc_no_orders_type() const { return alloc_no_orders_type_; }
void AllocationInstructionMessage::set_alloc_no_orders_type(AllocNoOrdersType value) { alloc_no_orders_type_ = value; }

std::uint64_t AllocationInstructionMessage::quantity() const { return quantity_; }
void AllocationInstructionMessage::set_quantity(std::uint64_t value) { quantity_ = value; }

const std::string& AllocationInstructionMessage::sender_location() const { return sender_location_; }
std::string& AllocationInstructionMessage::sender_location() { return sender_location_; }
void AllocationInstructionMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

const std::string& AllocationInstructionMessage::entering_trader() const { return entering_trader_; }
std::string& AllocationInstructionMessage::entering_trader() { return entering_trader_; }
void AllocationInstructionMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

std::uint32_t AllocationInstructionMessage::trade_id() const { return trade_id_; }
void AllocationInstructionMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::optional<std::uint16_t> AllocationInstructionMessage::trade_date_optional() const { return trade_date_optional_; }
void AllocationInstructionMessage::set_trade_date_optional(std::optional<std::uint16_t> value) { trade_date_optional_ = value; }

std::uint64_t AllocationInstructionMessage::individual_alloc_id() const { return individual_alloc_id_; }
void AllocationInstructionMessage::set_individual_alloc_id(std::uint64_t value) { individual_alloc_id_ = value; }

std::uint32_t AllocationInstructionMessage::alloc_account() const { return alloc_account_; }
void AllocationInstructionMessage::set_alloc_account(std::uint32_t value) { alloc_account_ = value; }

std::uint64_t AllocationInstructionMessage::alloc_qty() const { return alloc_qty_; }
void AllocationInstructionMessage::set_alloc_qty(std::uint64_t value) { alloc_qty_ = value; }

const DeskId& AllocationInstructionMessage::desk_id() const { return desk_id_; }
DeskId& AllocationInstructionMessage::desk_id() { return desk_id_; }
void AllocationInstructionMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& AllocationInstructionMessage::memo() const { return memo_; }
Memo& AllocationInstructionMessage::memo() { return memo_; }
void AllocationInstructionMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode AllocationInstructionMessage::type() const { return message_type; }

std::string_view AllocationInstructionMessage::name() const { return "Allocation Instruction Message"; }

std::size_t AllocationInstructionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += inbound_business_header_.decode(data + offset, length - offset);

    wire::require("AllocationInstructionMessage", offset + 8, length);
    alloc_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("AllocationInstructionMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("AllocationInstructionMessage", offset + 1, length);
    alloc_trans_type_ = static_cast<AllocTransType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("AllocationInstructionMessage", offset + 1, length);
    alloc_type_ = static_cast<AllocType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("AllocationInstructionMessage", offset + 1, length);
    alloc_no_orders_type_ = static_cast<AllocNoOrdersType>(wire::read_char(data + offset));
    offset += 1;

    wire::require("AllocationInstructionMessage", offset + 8, length);
    quantity_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("AllocationInstructionMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("AllocationInstructionMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("AllocationInstructionMessage", offset + 4, length);
    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("AllocationInstructionMessage", offset + 2, length);
    trade_date_optional_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    wire::require("AllocationInstructionMessage", offset + 8, length);
    individual_alloc_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("AllocationInstructionMessage", offset + 4, length);
    alloc_account_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("AllocationInstructionMessage", offset + 8, length);
    alloc_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t AllocationInstructionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AllocationInstructionMessage", encoded_size(), capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(alloc_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(alloc_trans_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(alloc_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(alloc_no_orders_type_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quantity_));
    offset += 8;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u16_le(data + offset, trade_date_optional_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(individual_alloc_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(alloc_account_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(alloc_qty_));
    offset += 8;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t AllocationInstructionMessage::encoded_size() const {
    return inbound_business_header_.encoded_size() + 8 + 8 + 1 + 1 + 1 + 8 + 10 + 5 + 4 + 2 + 8 + 4 + 8 + desk_id_.encoded_size() + memo_.encoded_size();
}

void AllocationInstructionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AllocationInstructionMessage::clone() const {
    return std::make_unique<AllocationInstructionMessage>(*this);
}

void AllocationInstructionMessage::print(std::ostream& out) const {
    out << "AllocationInstructionMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", alloc_id=";
    out << alloc_id_;
    out << ", security_id=";
    out << security_id_;
    out << ", alloc_trans_type=";
    out << alloc_trans_type_;
    out << ", alloc_type=";
    out << alloc_type_;
    out << ", alloc_no_orders_type=";
    out << alloc_no_orders_type_;
    out << ", quantity=";
    out << quantity_;
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", trade_id=";
    out << trade_id_;
    out << ", trade_date_optional=";
    print::optional(out, trade_date_optional_);
    out << ", individual_alloc_id=";
    out << individual_alloc_id_;
    out << ", alloc_account=";
    out << alloc_account_;
    out << ", alloc_qty=";
    out << alloc_qty_;
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool AllocationInstructionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AllocationInstructionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AllocationInstructionMessage::operator==(const AllocationInstructionMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && alloc_id_ == other.alloc_id_
        && security_id_ == other.security_id_
        && alloc_trans_type_ == other.alloc_trans_type_
        && alloc_type_ == other.alloc_type_
        && alloc_no_orders_type_ == other.alloc_no_orders_type_
        && quantity_ == other.quantity_
        && sender_location_ == other.sender_location_
        && entering_trader_ == other.entering_trader_
        && trade_id_ == other.trade_id_
        && trade_date_optional_ == other.trade_date_optional_
        && individual_alloc_id_ == other.individual_alloc_id_
        && alloc_account_ == other.alloc_account_
        && alloc_qty_ == other.alloc_qty_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool AllocationInstructionMessage::operator!=(const AllocationInstructionMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
