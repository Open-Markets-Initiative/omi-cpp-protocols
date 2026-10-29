#include "OrderMassActionReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

OrderMassActionReportMessage::OrderMassActionReportMessage(const OutboundBusinessHeader& outbound_business_header, MassActionType mass_action_type, std::optional<MassActionScope> mass_action_scope, std::uint64_t clordid, std::uint64_t mass_action_report_id, std::chrono::nanoseconds transact_time, MassActionResponse mass_action_response, std::optional<MassActionRejectReason> mass_action_reject_reason, std::optional<MassCancelRestatementReason> mass_cancel_restatement_reason, std::optional<std::uint8_t> ordtagid, SideOptional side_optional, const std::array<std::byte, 1>& offset_49_padding_1, const std::string& asset, std::optional<std::uint64_t> security_id_optional, const InvestorId& investor_id, const Text& text)
  : outbound_business_header_(outbound_business_header), mass_action_type_(mass_action_type), mass_action_scope_(mass_action_scope), clordid_(clordid), mass_action_report_id_(mass_action_report_id), transact_time_(transact_time), mass_action_response_(mass_action_response), mass_action_reject_reason_(mass_action_reject_reason), mass_cancel_restatement_reason_(mass_cancel_restatement_reason), ordtagid_(ordtagid), side_optional_(side_optional), offset_49_padding_1_(offset_49_padding_1), asset_(asset), security_id_optional_(security_id_optional), investor_id_(investor_id), text_(text) {}

const OutboundBusinessHeader& OrderMassActionReportMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& OrderMassActionReportMessage::outbound_business_header() { return outbound_business_header_; }
void OrderMassActionReportMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

MassActionType OrderMassActionReportMessage::mass_action_type() const { return mass_action_type_; }
void OrderMassActionReportMessage::set_mass_action_type(MassActionType value) { mass_action_type_ = value; }

std::optional<MassActionScope> OrderMassActionReportMessage::mass_action_scope() const { return mass_action_scope_; }
void OrderMassActionReportMessage::set_mass_action_scope(std::optional<MassActionScope> value) { mass_action_scope_ = value; }

std::uint64_t OrderMassActionReportMessage::clordid() const { return clordid_; }
void OrderMassActionReportMessage::set_clordid(std::uint64_t value) { clordid_ = value; }

std::uint64_t OrderMassActionReportMessage::mass_action_report_id() const { return mass_action_report_id_; }
void OrderMassActionReportMessage::set_mass_action_report_id(std::uint64_t value) { mass_action_report_id_ = value; }

std::chrono::nanoseconds OrderMassActionReportMessage::transact_time() const { return transact_time_; }
void OrderMassActionReportMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

MassActionResponse OrderMassActionReportMessage::mass_action_response() const { return mass_action_response_; }
void OrderMassActionReportMessage::set_mass_action_response(MassActionResponse value) { mass_action_response_ = value; }

std::optional<MassActionRejectReason> OrderMassActionReportMessage::mass_action_reject_reason() const { return mass_action_reject_reason_; }
void OrderMassActionReportMessage::set_mass_action_reject_reason(std::optional<MassActionRejectReason> value) { mass_action_reject_reason_ = value; }

std::optional<MassCancelRestatementReason> OrderMassActionReportMessage::mass_cancel_restatement_reason() const { return mass_cancel_restatement_reason_; }
void OrderMassActionReportMessage::set_mass_cancel_restatement_reason(std::optional<MassCancelRestatementReason> value) { mass_cancel_restatement_reason_ = value; }

std::optional<std::uint8_t> OrderMassActionReportMessage::ordtagid() const { return ordtagid_; }
void OrderMassActionReportMessage::set_ordtagid(std::optional<std::uint8_t> value) { ordtagid_ = value; }

SideOptional OrderMassActionReportMessage::side_optional() const { return side_optional_; }
void OrderMassActionReportMessage::set_side_optional(SideOptional value) { side_optional_ = value; }

const std::array<std::byte, 1>& OrderMassActionReportMessage::offset_49_padding_1() const { return offset_49_padding_1_; }
std::array<std::byte, 1>& OrderMassActionReportMessage::offset_49_padding_1() { return offset_49_padding_1_; }
void OrderMassActionReportMessage::set_offset_49_padding_1(const std::array<std::byte, 1>& value) { offset_49_padding_1_ = value; }

const std::string& OrderMassActionReportMessage::asset() const { return asset_; }
std::string& OrderMassActionReportMessage::asset() { return asset_; }
void OrderMassActionReportMessage::set_asset(const std::string& value) { asset_ = value; }

std::optional<std::uint64_t> OrderMassActionReportMessage::security_id_optional() const { return security_id_optional_; }
void OrderMassActionReportMessage::set_security_id_optional(std::optional<std::uint64_t> value) { security_id_optional_ = value; }

const InvestorId& OrderMassActionReportMessage::investor_id() const { return investor_id_; }
InvestorId& OrderMassActionReportMessage::investor_id() { return investor_id_; }
void OrderMassActionReportMessage::set_investor_id(const InvestorId& value) { investor_id_ = value; }

const Text& OrderMassActionReportMessage::text() const { return text_; }
Text& OrderMassActionReportMessage::text() { return text_; }
void OrderMassActionReportMessage::set_text(const Text& value) { text_ = value; }

MessageCode OrderMassActionReportMessage::type() const { return message_type; }

std::string_view OrderMassActionReportMessage::name() const { return "Order Mass Action Report Message"; }

std::size_t OrderMassActionReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    mass_action_type_ = static_cast<MassActionType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    mass_action_scope_ = wire::nullable_enum<MassActionScope>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 8, length);
    clordid_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("OrderMassActionReportMessage", offset + 8, length);
    mass_action_report_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("OrderMassActionReportMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    mass_action_response_ = static_cast<MassActionResponse>(wire::read_char(data + offset));
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    mass_action_reject_reason_ = wire::nullable_enum<MassActionRejectReason>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    mass_cancel_restatement_reason_ = wire::nullable_enum<MassCancelRestatementReason>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    ordtagid_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    side_optional_ = static_cast<SideOptional>(wire::read_char(data + offset));
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 1, length);
    wire::read_bytes(data + offset, offset_49_padding_1_.data(), 1);
    offset += 1;

    wire::require("OrderMassActionReportMessage", offset + 6, length);
    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("OrderMassActionReportMessage", offset + 8, length);
    security_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    offset += investor_id_.decode(data + offset, length - offset);

    offset += text_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderMassActionReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderMassActionReportMessage", encoded_size(), capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(mass_action_type_));
    offset += 1;

    wire::write_u8(data + offset, mass_action_scope_ ? static_cast<std::uint8_t>(*mass_action_scope_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(clordid_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(mass_action_report_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(mass_action_response_));
    offset += 1;

    wire::write_u8(data + offset, mass_action_reject_reason_ ? static_cast<std::uint8_t>(*mass_action_reject_reason_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, mass_cancel_restatement_reason_ ? static_cast<std::uint8_t>(*mass_cancel_restatement_reason_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, ordtagid_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_optional_));
    offset += 1;

    wire::write_bytes(data + offset, offset_49_padding_1_.data(), 1);
    offset += 1;

    wire::write_text(data + offset, 6, '\0', asset_);
    offset += 6;

    wire::write_u64_le(data + offset, security_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    offset += investor_id_.encode(data + offset, capacity - offset);

    offset += text_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderMassActionReportMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 1 + 1 + 8 + 8 + 8 + 1 + 1 + 1 + 1 + 1 + 1 + 6 + 8 + investor_id_.encoded_size() + text_.encoded_size();
}

void OrderMassActionReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderMassActionReportMessage::clone() const {
    return std::make_unique<OrderMassActionReportMessage>(*this);
}

void OrderMassActionReportMessage::print(std::ostream& out) const {
    out << "OrderMassActionReportMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", mass_action_type=";
    out << mass_action_type_;
    out << ", mass_action_scope=";
    print::optional(out, mass_action_scope_);
    out << ", clordid=";
    out << clordid_;
    out << ", mass_action_report_id=";
    out << mass_action_report_id_;
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", mass_action_response=";
    out << mass_action_response_;
    out << ", mass_action_reject_reason=";
    print::optional(out, mass_action_reject_reason_);
    out << ", mass_cancel_restatement_reason=";
    print::optional(out, mass_cancel_restatement_reason_);
    out << ", ordtagid=";
    print::optional(out, ordtagid_);
    out << ", side_optional=";
    out << side_optional_;
    out << ", offset_49_padding_1=";
    print::hex(out, offset_49_padding_1_.data(), offset_49_padding_1_.size());
    out << ", asset=";
    print::text(out, asset_);
    out << ", security_id_optional=";
    print::optional(out, security_id_optional_);
    out << ", investor_id=";
    investor_id_.print(out);
    out << ", text=";
    text_.print(out);
    out << '}';
}

bool OrderMassActionReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderMassActionReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderMassActionReportMessage::operator==(const OrderMassActionReportMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && mass_action_type_ == other.mass_action_type_
        && mass_action_scope_ == other.mass_action_scope_
        && clordid_ == other.clordid_
        && mass_action_report_id_ == other.mass_action_report_id_
        && transact_time_ == other.transact_time_
        && mass_action_response_ == other.mass_action_response_
        && mass_action_reject_reason_ == other.mass_action_reject_reason_
        && mass_cancel_restatement_reason_ == other.mass_cancel_restatement_reason_
        && ordtagid_ == other.ordtagid_
        && side_optional_ == other.side_optional_
        && offset_49_padding_1_ == other.offset_49_padding_1_
        && asset_ == other.asset_
        && security_id_optional_ == other.security_id_optional_
        && investor_id_ == other.investor_id_
        && text_ == other.text_;
}

bool OrderMassActionReportMessage::operator!=(const OrderMassActionReportMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
