#include "PositionMaintenanceRequestMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

PositionMaintenanceRequestMessage::PositionMaintenanceRequestMessage(const InboundBusinessHeader& inbound_business_header, std::uint64_t pos_req_id, std::uint64_t security_id, std::optional<Decimal> threshold_amount, std::optional<std::uint32_t> account, const std::string& sender_location, PosTransType pos_trans_type, std::uint16_t clearing_business_date, ContraryInstructionIndicator contrary_instruction_indicator, const std::string& entering_trader, std::uint64_t long_qty, const DeskId& desk_id, const Memo& memo)
  : inbound_business_header_(inbound_business_header), pos_req_id_(pos_req_id), security_id_(security_id), threshold_amount_(threshold_amount), account_(account), sender_location_(sender_location), pos_trans_type_(pos_trans_type), clearing_business_date_(clearing_business_date), contrary_instruction_indicator_(contrary_instruction_indicator), entering_trader_(entering_trader), long_qty_(long_qty), desk_id_(desk_id), memo_(memo) {}

const InboundBusinessHeader& PositionMaintenanceRequestMessage::inbound_business_header() const { return inbound_business_header_; }
InboundBusinessHeader& PositionMaintenanceRequestMessage::inbound_business_header() { return inbound_business_header_; }
void PositionMaintenanceRequestMessage::set_inbound_business_header(const InboundBusinessHeader& value) { inbound_business_header_ = value; }

std::uint64_t PositionMaintenanceRequestMessage::pos_req_id() const { return pos_req_id_; }
void PositionMaintenanceRequestMessage::set_pos_req_id(std::uint64_t value) { pos_req_id_ = value; }

std::uint64_t PositionMaintenanceRequestMessage::security_id() const { return security_id_; }
void PositionMaintenanceRequestMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::optional<Decimal> PositionMaintenanceRequestMessage::threshold_amount() const { return threshold_amount_; }
void PositionMaintenanceRequestMessage::set_threshold_amount(std::optional<Decimal> value) { threshold_amount_ = value; }

std::optional<std::uint32_t> PositionMaintenanceRequestMessage::account() const { return account_; }
void PositionMaintenanceRequestMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

const std::string& PositionMaintenanceRequestMessage::sender_location() const { return sender_location_; }
std::string& PositionMaintenanceRequestMessage::sender_location() { return sender_location_; }
void PositionMaintenanceRequestMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

PosTransType PositionMaintenanceRequestMessage::pos_trans_type() const { return pos_trans_type_; }
void PositionMaintenanceRequestMessage::set_pos_trans_type(PosTransType value) { pos_trans_type_ = value; }

std::uint16_t PositionMaintenanceRequestMessage::clearing_business_date() const { return clearing_business_date_; }
void PositionMaintenanceRequestMessage::set_clearing_business_date(std::uint16_t value) { clearing_business_date_ = value; }

ContraryInstructionIndicator PositionMaintenanceRequestMessage::contrary_instruction_indicator() const { return contrary_instruction_indicator_; }
void PositionMaintenanceRequestMessage::set_contrary_instruction_indicator(ContraryInstructionIndicator value) { contrary_instruction_indicator_ = value; }

const std::string& PositionMaintenanceRequestMessage::entering_trader() const { return entering_trader_; }
std::string& PositionMaintenanceRequestMessage::entering_trader() { return entering_trader_; }
void PositionMaintenanceRequestMessage::set_entering_trader(const std::string& value) { entering_trader_ = value; }

std::uint64_t PositionMaintenanceRequestMessage::long_qty() const { return long_qty_; }
void PositionMaintenanceRequestMessage::set_long_qty(std::uint64_t value) { long_qty_ = value; }

const DeskId& PositionMaintenanceRequestMessage::desk_id() const { return desk_id_; }
DeskId& PositionMaintenanceRequestMessage::desk_id() { return desk_id_; }
void PositionMaintenanceRequestMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& PositionMaintenanceRequestMessage::memo() const { return memo_; }
Memo& PositionMaintenanceRequestMessage::memo() { return memo_; }
void PositionMaintenanceRequestMessage::set_memo(const Memo& value) { memo_ = value; }

MessageCode PositionMaintenanceRequestMessage::type() const { return message_type; }

std::string_view PositionMaintenanceRequestMessage::name() const { return "Position Maintenance Request Message"; }

std::size_t PositionMaintenanceRequestMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += inbound_business_header_.decode(data + offset, length - offset);

    wire::require("PositionMaintenanceRequestMessage", offset + 8, length);
    pos_req_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("PositionMaintenanceRequestMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("PositionMaintenanceRequestMessage", offset + 8, length);
    threshold_amount_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("PositionMaintenanceRequestMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("PositionMaintenanceRequestMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("PositionMaintenanceRequestMessage", offset + 1, length);
    pos_trans_type_ = static_cast<PosTransType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("PositionMaintenanceRequestMessage", offset + 2, length);
    clearing_business_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("PositionMaintenanceRequestMessage", offset + 1, length);
    contrary_instruction_indicator_ = static_cast<ContraryInstructionIndicator>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("PositionMaintenanceRequestMessage", offset + 5, length);
    entering_trader_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("PositionMaintenanceRequestMessage", offset + 8, length);
    long_qty_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    return offset;
}

std::size_t PositionMaintenanceRequestMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PositionMaintenanceRequestMessage", encoded_size(), capacity);

    offset += inbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(pos_req_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_i64_le(data + offset, threshold_amount_ ? static_cast<std::int64_t>(threshold_amount_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(pos_trans_type_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(clearing_business_date_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(contrary_instruction_indicator_));
    offset += 1;

    wire::write_text(data + offset, 5, '\0', entering_trader_);
    offset += 5;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(long_qty_));
    offset += 8;

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t PositionMaintenanceRequestMessage::encoded_size() const {
    return inbound_business_header_.encoded_size() + 8 + 8 + 8 + 4 + 10 + 1 + 2 + 1 + 5 + 8 + desk_id_.encoded_size() + memo_.encoded_size();
}

void PositionMaintenanceRequestMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PositionMaintenanceRequestMessage::clone() const {
    return std::make_unique<PositionMaintenanceRequestMessage>(*this);
}

void PositionMaintenanceRequestMessage::print(std::ostream& out) const {
    out << "PositionMaintenanceRequestMessage{";
    out << "inbound_business_header=";
    inbound_business_header_.print(out);
    out << ", pos_req_id=";
    out << pos_req_id_;
    out << ", security_id=";
    out << security_id_;
    out << ", threshold_amount=";
    print::optional(out, threshold_amount_);
    out << ", account=";
    print::optional(out, account_);
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", pos_trans_type=";
    out << pos_trans_type_;
    out << ", clearing_business_date=";
    out << clearing_business_date_;
    out << ", contrary_instruction_indicator=";
    out << contrary_instruction_indicator_;
    out << ", entering_trader=";
    print::text(out, entering_trader_);
    out << ", long_qty=";
    out << long_qty_;
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << '}';
}

bool PositionMaintenanceRequestMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PositionMaintenanceRequestMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PositionMaintenanceRequestMessage::operator==(const PositionMaintenanceRequestMessage& other) const {
    return inbound_business_header_ == other.inbound_business_header_
        && pos_req_id_ == other.pos_req_id_
        && security_id_ == other.security_id_
        && threshold_amount_ == other.threshold_amount_
        && account_ == other.account_
        && sender_location_ == other.sender_location_
        && pos_trans_type_ == other.pos_trans_type_
        && clearing_business_date_ == other.clearing_business_date_
        && contrary_instruction_indicator_ == other.contrary_instruction_indicator_
        && entering_trader_ == other.entering_trader_
        && long_qty_ == other.long_qty_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_;
}

bool PositionMaintenanceRequestMessage::operator!=(const PositionMaintenanceRequestMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
