#include "PositionMaintenanceReportMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

PositionMaintenanceReportMessage::PositionMaintenanceReportMessage(const OutboundBusinessHeader& outbound_business_header, std::optional<std::uint64_t> pos_req_id_optional, std::uint64_t security_id, std::uint64_t pos_maint_rpt_id, PosTransType pos_trans_type, PosMaintAction pos_maint_action, PosMaintStatus pos_maint_status, std::optional<std::uint32_t> trade_id_optional, std::optional<std::uint64_t> orig_pos_req_ref_id, std::optional<AccountType> account_type, std::uint16_t clearing_business_date, std::optional<Decimal> threshold_amount, std::chrono::nanoseconds transact_time, std::optional<std::uint32_t> account, const std::string& sender_location, std::optional<std::uint32_t> pos_maint_result, ContraryInstructionIndicator contrary_instruction_indicator, const PositionsGroups& positions_groups, const DeskId& desk_id, const Memo& memo, const Text& text)
  : outbound_business_header_(outbound_business_header), pos_req_id_optional_(pos_req_id_optional), security_id_(security_id), pos_maint_rpt_id_(pos_maint_rpt_id), pos_trans_type_(pos_trans_type), pos_maint_action_(pos_maint_action), pos_maint_status_(pos_maint_status), trade_id_optional_(trade_id_optional), orig_pos_req_ref_id_(orig_pos_req_ref_id), account_type_(account_type), clearing_business_date_(clearing_business_date), threshold_amount_(threshold_amount), transact_time_(transact_time), account_(account), sender_location_(sender_location), pos_maint_result_(pos_maint_result), contrary_instruction_indicator_(contrary_instruction_indicator), positions_groups_(positions_groups), desk_id_(desk_id), memo_(memo), text_(text) {}

const OutboundBusinessHeader& PositionMaintenanceReportMessage::outbound_business_header() const { return outbound_business_header_; }
OutboundBusinessHeader& PositionMaintenanceReportMessage::outbound_business_header() { return outbound_business_header_; }
void PositionMaintenanceReportMessage::set_outbound_business_header(const OutboundBusinessHeader& value) { outbound_business_header_ = value; }

std::optional<std::uint64_t> PositionMaintenanceReportMessage::pos_req_id_optional() const { return pos_req_id_optional_; }
void PositionMaintenanceReportMessage::set_pos_req_id_optional(std::optional<std::uint64_t> value) { pos_req_id_optional_ = value; }

std::uint64_t PositionMaintenanceReportMessage::security_id() const { return security_id_; }
void PositionMaintenanceReportMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

std::uint64_t PositionMaintenanceReportMessage::pos_maint_rpt_id() const { return pos_maint_rpt_id_; }
void PositionMaintenanceReportMessage::set_pos_maint_rpt_id(std::uint64_t value) { pos_maint_rpt_id_ = value; }

PosTransType PositionMaintenanceReportMessage::pos_trans_type() const { return pos_trans_type_; }
void PositionMaintenanceReportMessage::set_pos_trans_type(PosTransType value) { pos_trans_type_ = value; }

PosMaintAction PositionMaintenanceReportMessage::pos_maint_action() const { return pos_maint_action_; }
void PositionMaintenanceReportMessage::set_pos_maint_action(PosMaintAction value) { pos_maint_action_ = value; }

PosMaintStatus PositionMaintenanceReportMessage::pos_maint_status() const { return pos_maint_status_; }
void PositionMaintenanceReportMessage::set_pos_maint_status(PosMaintStatus value) { pos_maint_status_ = value; }

std::optional<std::uint32_t> PositionMaintenanceReportMessage::trade_id_optional() const { return trade_id_optional_; }
void PositionMaintenanceReportMessage::set_trade_id_optional(std::optional<std::uint32_t> value) { trade_id_optional_ = value; }

std::optional<std::uint64_t> PositionMaintenanceReportMessage::orig_pos_req_ref_id() const { return orig_pos_req_ref_id_; }
void PositionMaintenanceReportMessage::set_orig_pos_req_ref_id(std::optional<std::uint64_t> value) { orig_pos_req_ref_id_ = value; }

std::optional<AccountType> PositionMaintenanceReportMessage::account_type() const { return account_type_; }
void PositionMaintenanceReportMessage::set_account_type(std::optional<AccountType> value) { account_type_ = value; }

std::uint16_t PositionMaintenanceReportMessage::clearing_business_date() const { return clearing_business_date_; }
void PositionMaintenanceReportMessage::set_clearing_business_date(std::uint16_t value) { clearing_business_date_ = value; }

std::optional<Decimal> PositionMaintenanceReportMessage::threshold_amount() const { return threshold_amount_; }
void PositionMaintenanceReportMessage::set_threshold_amount(std::optional<Decimal> value) { threshold_amount_ = value; }

std::chrono::nanoseconds PositionMaintenanceReportMessage::transact_time() const { return transact_time_; }
void PositionMaintenanceReportMessage::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::optional<std::uint32_t> PositionMaintenanceReportMessage::account() const { return account_; }
void PositionMaintenanceReportMessage::set_account(std::optional<std::uint32_t> value) { account_ = value; }

const std::string& PositionMaintenanceReportMessage::sender_location() const { return sender_location_; }
std::string& PositionMaintenanceReportMessage::sender_location() { return sender_location_; }
void PositionMaintenanceReportMessage::set_sender_location(const std::string& value) { sender_location_ = value; }

std::optional<std::uint32_t> PositionMaintenanceReportMessage::pos_maint_result() const { return pos_maint_result_; }
void PositionMaintenanceReportMessage::set_pos_maint_result(std::optional<std::uint32_t> value) { pos_maint_result_ = value; }

ContraryInstructionIndicator PositionMaintenanceReportMessage::contrary_instruction_indicator() const { return contrary_instruction_indicator_; }
void PositionMaintenanceReportMessage::set_contrary_instruction_indicator(ContraryInstructionIndicator value) { contrary_instruction_indicator_ = value; }

const PositionsGroups& PositionMaintenanceReportMessage::positions_groups() const { return positions_groups_; }
PositionsGroups& PositionMaintenanceReportMessage::positions_groups() { return positions_groups_; }
void PositionMaintenanceReportMessage::set_positions_groups(const PositionsGroups& value) { positions_groups_ = value; }

const DeskId& PositionMaintenanceReportMessage::desk_id() const { return desk_id_; }
DeskId& PositionMaintenanceReportMessage::desk_id() { return desk_id_; }
void PositionMaintenanceReportMessage::set_desk_id(const DeskId& value) { desk_id_ = value; }

const Memo& PositionMaintenanceReportMessage::memo() const { return memo_; }
Memo& PositionMaintenanceReportMessage::memo() { return memo_; }
void PositionMaintenanceReportMessage::set_memo(const Memo& value) { memo_ = value; }

const Text& PositionMaintenanceReportMessage::text() const { return text_; }
Text& PositionMaintenanceReportMessage::text() { return text_; }
void PositionMaintenanceReportMessage::set_text(const Text& value) { text_ = value; }

MessageCode PositionMaintenanceReportMessage::type() const { return message_type; }

std::string_view PositionMaintenanceReportMessage::name() const { return "Position Maintenance Report Message"; }

std::size_t PositionMaintenanceReportMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += outbound_business_header_.decode(data + offset, length - offset);

    wire::require("PositionMaintenanceReportMessage", offset + 8, length);
    pos_req_id_optional_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("PositionMaintenanceReportMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("PositionMaintenanceReportMessage", offset + 8, length);
    pos_maint_rpt_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("PositionMaintenanceReportMessage", offset + 1, length);
    pos_trans_type_ = static_cast<PosTransType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("PositionMaintenanceReportMessage", offset + 1, length);
    pos_maint_action_ = static_cast<PosMaintAction>(wire::read_char(data + offset));
    offset += 1;

    wire::require("PositionMaintenanceReportMessage", offset + 1, length);
    pos_maint_status_ = static_cast<PosMaintStatus>(wire::read_char(data + offset));
    offset += 1;

    wire::require("PositionMaintenanceReportMessage", offset + 4, length);
    trade_id_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("PositionMaintenanceReportMessage", offset + 8, length);
    orig_pos_req_ref_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("PositionMaintenanceReportMessage", offset + 1, length);
    account_type_ = wire::nullable_enum<AccountType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("PositionMaintenanceReportMessage", offset + 2, length);
    clearing_business_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("PositionMaintenanceReportMessage", offset + 8, length);
    threshold_amount_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("PositionMaintenanceReportMessage", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("PositionMaintenanceReportMessage", offset + 4, length);
    account_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("PositionMaintenanceReportMessage", offset + 10, length);
    sender_location_ = wire::read_text(data + offset, 10, '\0');
    offset += 10;

    wire::require("PositionMaintenanceReportMessage", offset + 4, length);
    pos_maint_result_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("PositionMaintenanceReportMessage", offset + 1, length);
    contrary_instruction_indicator_ = static_cast<ContraryInstructionIndicator>(wire::read_u8(data + offset));
    offset += 1;

    offset += positions_groups_.decode(data + offset, length - offset);

    offset += desk_id_.decode(data + offset, length - offset);

    offset += memo_.decode(data + offset, length - offset);

    offset += text_.decode(data + offset, length - offset);

    return offset;
}

std::size_t PositionMaintenanceReportMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PositionMaintenanceReportMessage", encoded_size(), capacity);

    offset += outbound_business_header_.encode(data + offset, capacity - offset);

    wire::write_u64_le(data + offset, pos_req_id_optional_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(pos_maint_rpt_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(pos_trans_type_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(pos_maint_action_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(pos_maint_status_));
    offset += 1;

    wire::write_u32_le(data + offset, trade_id_optional_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, orig_pos_req_ref_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u8(data + offset, account_type_ ? static_cast<std::uint8_t>(*account_type_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(clearing_business_date_));
    offset += 2;

    wire::write_i64_le(data + offset, threshold_amount_ ? static_cast<std::int64_t>(threshold_amount_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, account_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_text(data + offset, 10, '\0', sender_location_);
    offset += 10;

    wire::write_u32_le(data + offset, pos_maint_result_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(contrary_instruction_indicator_));
    offset += 1;

    offset += positions_groups_.encode(data + offset, capacity - offset);

    offset += desk_id_.encode(data + offset, capacity - offset);

    offset += memo_.encode(data + offset, capacity - offset);

    offset += text_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t PositionMaintenanceReportMessage::encoded_size() const {
    return outbound_business_header_.encoded_size() + 8 + 8 + 8 + 1 + 1 + 1 + 4 + 8 + 1 + 2 + 8 + 8 + 4 + 10 + 4 + 1 + positions_groups_.encoded_size() + desk_id_.encoded_size() + memo_.encoded_size() + text_.encoded_size();
}

void PositionMaintenanceReportMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PositionMaintenanceReportMessage::clone() const {
    return std::make_unique<PositionMaintenanceReportMessage>(*this);
}

void PositionMaintenanceReportMessage::print(std::ostream& out) const {
    out << "PositionMaintenanceReportMessage{";
    out << "outbound_business_header=";
    outbound_business_header_.print(out);
    out << ", pos_req_id_optional=";
    print::optional(out, pos_req_id_optional_);
    out << ", security_id=";
    out << security_id_;
    out << ", pos_maint_rpt_id=";
    out << pos_maint_rpt_id_;
    out << ", pos_trans_type=";
    out << pos_trans_type_;
    out << ", pos_maint_action=";
    out << pos_maint_action_;
    out << ", pos_maint_status=";
    out << pos_maint_status_;
    out << ", trade_id_optional=";
    print::optional(out, trade_id_optional_);
    out << ", orig_pos_req_ref_id=";
    print::optional(out, orig_pos_req_ref_id_);
    out << ", account_type=";
    print::optional(out, account_type_);
    out << ", clearing_business_date=";
    out << clearing_business_date_;
    out << ", threshold_amount=";
    print::optional(out, threshold_amount_);
    out << ", transact_time=";
    out << transact_time_.count();
    out << ", account=";
    print::optional(out, account_);
    out << ", sender_location=";
    print::text(out, sender_location_);
    out << ", pos_maint_result=";
    print::optional(out, pos_maint_result_);
    out << ", contrary_instruction_indicator=";
    out << contrary_instruction_indicator_;
    out << ", positions_groups=";
    positions_groups_.print(out);
    out << ", desk_id=";
    desk_id_.print(out);
    out << ", memo=";
    memo_.print(out);
    out << ", text=";
    text_.print(out);
    out << '}';
}

bool PositionMaintenanceReportMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PositionMaintenanceReportMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PositionMaintenanceReportMessage::operator==(const PositionMaintenanceReportMessage& other) const {
    return outbound_business_header_ == other.outbound_business_header_
        && pos_req_id_optional_ == other.pos_req_id_optional_
        && security_id_ == other.security_id_
        && pos_maint_rpt_id_ == other.pos_maint_rpt_id_
        && pos_trans_type_ == other.pos_trans_type_
        && pos_maint_action_ == other.pos_maint_action_
        && pos_maint_status_ == other.pos_maint_status_
        && trade_id_optional_ == other.trade_id_optional_
        && orig_pos_req_ref_id_ == other.orig_pos_req_ref_id_
        && account_type_ == other.account_type_
        && clearing_business_date_ == other.clearing_business_date_
        && threshold_amount_ == other.threshold_amount_
        && transact_time_ == other.transact_time_
        && account_ == other.account_
        && sender_location_ == other.sender_location_
        && pos_maint_result_ == other.pos_maint_result_
        && contrary_instruction_indicator_ == other.contrary_instruction_indicator_
        && positions_groups_ == other.positions_groups_
        && desk_id_ == other.desk_id_
        && memo_ == other.memo_
        && text_ == other.text_;
}

bool PositionMaintenanceReportMessage::operator!=(const PositionMaintenanceReportMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
