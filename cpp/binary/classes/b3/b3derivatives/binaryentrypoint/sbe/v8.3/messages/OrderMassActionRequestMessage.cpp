#include "OrderMassActionRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

OrderMassActionRequestMessage::OrderMassActionRequestMessage(const InboundBusinessHeader& inbound_business_header, MassActionType mass_action_type, std::optional<MassActionScope> mass_action_scope, std::uint64_t clordid, std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason, std::optional<std::uint8_t> ordtagid, SideOptional side_optional, const std::array<std::byte, 1>& offset_31_padding_1, const std::string& asset, std::optional<std::uint64_t> security_id_optional, const InvestorId& investor_id)
  : inbound_business_header_(inbound_business_header), mass_action_type_(mass_action_type), mass_action_scope_(mass_action_scope), clordid_(clordid), mass_cancel_restatement_reason_(mass_cancel_restatement_reason), ordtagid_(ordtagid), side_optional_(side_optional), offset_31_padding_1_(offset_31_padding_1), asset_(asset), security_id_optional_(security_id_optional), investor_id_(investor_id) {}

const InboundBusinessHeader& OrderMassActionRequestMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& OrderMassActionRequestMessage::inbound_business_header() { return inbound_business_header_; }
void OrderMassActionRequestMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

MassActionType OrderMassActionRequestMessage::mass_action_type() const { return mass_action_type_; }
void OrderMassActionRequestMessage::set_mass_action_type(MassActionType value) { mass_action_type_ = value; }

std::optional<MassActionScope> OrderMassActionRequestMessage::mass_action_scope() const { return mass_action_scope_; }
void OrderMassActionRequestMessage::set_mass_action_scope(std::optional<MassActionScope> value) { mass_action_scope_ = value; }

std::uint64_t OrderMassActionRequestMessage::clordid() const { return clordid_; }
void OrderMassActionRequestMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::optional<MassCancelRestatementReason> OrderMassActionRequestMessage::mass_cancel_restatement_reason() const { return mass_cancel_restatement_reason_; }
void OrderMassActionRequestMessage::set_mass_cancel_restatement_reason(std::optional<MassCancelRestatementReason> value) { mass_cancel_restatement_reason_ = value; }

std::optional<std::uint8_t> OrderMassActionRequestMessage::ordtagid() const { return ordtagid_; }
void OrderMassActionRequestMessage::set_ordtagid(std::optional<std::uint8_t> value) { ordtagid_ = value; }

SideOptional OrderMassActionRequestMessage::side_optional() const { return side_optional_; }
void OrderMassActionRequestMessage::set_side_optional(SideOptional value) { side_optional_ = value; }

const std::array<std::byte, 1>& OrderMassActionRequestMessage::offset_31_padding_1() const { return offset_31_padding_1_; }
std::array<std::byte, 1>& OrderMassActionRequestMessage::offset_31_padding_1() { return offset_31_padding_1_; }
void OrderMassActionRequestMessage::set_offset_31_padding_1(const std::array<std::byte, 1>& value) { offset_31_padding_1_ = value; }

const std::string& OrderMassActionRequestMessage::asset() const { return asset_; }
std::string& OrderMassActionRequestMessage::asset() { return asset_; }
void OrderMassActionRequestMessage::set_asset(const std::string& value) { asset_ = value; }

std::optional<std::uint64_t> OrderMassActionRequestMessage::security_id_optional() const { return security_id_optional_; }
void OrderMassActionRequestMessage::set_security_id_optional(std::optional<std::uint64_t> value) { security_id_optional_ = value; }

const InvestorId& OrderMassActionRequestMessage::investor_id() const { return investor_id_; }
InvestorId& OrderMassActionRequestMessage::investor_id() { return investor_id_; }
void OrderMassActionRequestMessage::set_investor_id(const InvestorId& value) { investor_id_ = value; }

MessageCode OrderMassActionRequestMessage::type() const { return message_type; }

std::string_view OrderMassActionRequestMessage::name() const { return "Order Mass Action Request Message"; }

std::size_t OrderMassActionRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderMassActionRequestMessage", wire_size, length);

    offset += inbound_business_header_.decode(data + offset, length - offset);

    mass_action_type_ = static_cast<MassActionType>(wire::read_u8(data + offset));
    offset += 1;

    mass_action_scope_ = wire::nullable_enum<MassActionScope>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    mass_cancel_restatement_reason_ = wire::nullable_enum<MassCancelRestatementReason>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    ordtagid_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    side_optional_ = static_cast<SideOptional>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_31_padding_1_.data(), 1);
    offset += 1;

    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    security_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    offset += investor_id_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderMassActionRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderMassActionRequestMessage", wire_size, capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(mass_action_type_));
    offset += 1;

    wire::write_u8(data + offset, mass_action_scope_ ? static_cast<std::uint8_t>(*mass_action_scope_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(clordid_));
    offset += 8;

    wire::write_u8(data + offset, mass_cancel_restatement_reason_ ? static_cast<std::uint8_t>(*mass_cancel_restatement_reason_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, ordtagid_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_optional_));
    offset += 1;

    wire::write_bytes(data + offset, offset_31_padding_1_.data(), 1);
    offset += 1;

    wire::write_text(data + offset, 6, '\0', asset_);
    offset += 6;

    wire::write_u64_le(data + offset, security_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    offset += investor_id_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderMassActionRequestMessage::encoded_size() const {
    return wire_size;
}

void OrderMassActionRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderMassActionRequestMessage::clone() const {
    return std::make_unique<OrderMassActionRequestMessage>(*this);
}

void OrderMassActionRequestMessage::print(std::ostream& out) const {
    out << "OrderMassActionRequestMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", mass_action_type=";
    out << mass_action_type_;
    out << ", mass_action_scope=";
    print::optional(out, mass_action_scope_);
    out << ", clordid=";
    out << clordid_;
    out << ", mass_cancel_restatement_reason=";
    print::optional(out, mass_cancel_restatement_reason_);
    out << ", ordtagid=";
    print::optional(out, ordtagid_);
    out << ", side_optional=";
    out << side_optional_;
    out << ", offset_31_padding_1=";
    print::hex(out, offset_31_padding_1_.data(), offset_31_padding_1_.size());
    out << ", asset=";
    print::text(out, asset_);
    out << ", security_id_optional=";
    print::optional(out, security_id_optional_);
    out << ", investor_id=";
    investor_id_.print(out);
    out << '}';
}

bool OrderMassActionRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderMassActionRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderMassActionRequestMessage::operator==(const OrderMassActionRequestMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && mass_action_type_ == other.mass_action_type_
        && mass_action_scope_ == other.mass_action_scope_
        && clordid_ == other.clordid_
        && mass_cancel_restatement_reason_ == other.mass_cancel_restatement_reason_
        && ordtagid_ == other.ordtagid_
        && side_optional_ == other.side_optional_
        && offset_31_padding_1_ == other.offset_31_padding_1_
        && asset_ == other.asset_
        && security_id_optional_ == other.security_id_optional_
        && investor_id_ == other.investor_id_;
}

bool OrderMassActionRequestMessage::operator!=(const OrderMassActionRequestMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
