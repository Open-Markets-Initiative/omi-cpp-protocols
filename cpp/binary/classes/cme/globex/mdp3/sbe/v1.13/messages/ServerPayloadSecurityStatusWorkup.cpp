#include "ServerPayloadSecurityStatusWorkup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ServerPayloadSecurityStatusWorkup::ServerPayloadSecurityStatusWorkup(std::chrono::nanoseconds transact_time, std::optional<Decimal> md_entry_px_optional_ex, std::int32_t security_id, const MatchEventIndicator& match_event_indicator, std::optional<std::uint16_t> trade_date, std::uint32_t trade_link_id, WorkupTradingStatus workup_trading_status, HaltReason halt_reason, SecurityTradingEvent security_trading_event, const SecurityStatusWorkupGroups& security_status_workup_groups)
  : transact_time_(transact_time), md_entry_px_optional_ex_(md_entry_px_optional_ex), security_id_(security_id), match_event_indicator_(match_event_indicator), trade_date_(trade_date), trade_link_id_(trade_link_id), workup_trading_status_(workup_trading_status), halt_reason_(halt_reason), security_trading_event_(security_trading_event), security_status_workup_groups_(security_status_workup_groups) {}

std::chrono::nanoseconds ServerPayloadSecurityStatusWorkup::transact_time() const { return transact_time_; }
void ServerPayloadSecurityStatusWorkup::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

std::optional<Decimal> ServerPayloadSecurityStatusWorkup::md_entry_px_optional_ex() const { return md_entry_px_optional_ex_; }
void ServerPayloadSecurityStatusWorkup::set_md_entry_px_optional_ex(std::optional<Decimal> value) { md_entry_px_optional_ex_ = value; }

std::int32_t ServerPayloadSecurityStatusWorkup::security_id() const { return security_id_; }
void ServerPayloadSecurityStatusWorkup::set_security_id(std::int32_t value) { security_id_ = value; }

const MatchEventIndicator& ServerPayloadSecurityStatusWorkup::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadSecurityStatusWorkup::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadSecurityStatusWorkup::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<std::uint16_t> ServerPayloadSecurityStatusWorkup::trade_date() const { return trade_date_; }
void ServerPayloadSecurityStatusWorkup::set_trade_date(std::optional<std::uint16_t> value) { trade_date_ = value; }

std::uint32_t ServerPayloadSecurityStatusWorkup::trade_link_id() const { return trade_link_id_; }
void ServerPayloadSecurityStatusWorkup::set_trade_link_id(std::uint32_t value) { trade_link_id_ = value; }

WorkupTradingStatus ServerPayloadSecurityStatusWorkup::workup_trading_status() const { return workup_trading_status_; }
void ServerPayloadSecurityStatusWorkup::set_workup_trading_status(WorkupTradingStatus value) { workup_trading_status_ = value; }

HaltReason ServerPayloadSecurityStatusWorkup::halt_reason() const { return halt_reason_; }
void ServerPayloadSecurityStatusWorkup::set_halt_reason(HaltReason value) { halt_reason_ = value; }

SecurityTradingEvent ServerPayloadSecurityStatusWorkup::security_trading_event() const { return security_trading_event_; }
void ServerPayloadSecurityStatusWorkup::set_security_trading_event(SecurityTradingEvent value) { security_trading_event_ = value; }

const SecurityStatusWorkupGroups& ServerPayloadSecurityStatusWorkup::security_status_workup_groups() const { return security_status_workup_groups_; }
SecurityStatusWorkupGroups& ServerPayloadSecurityStatusWorkup::security_status_workup_groups() { return security_status_workup_groups_; }
void ServerPayloadSecurityStatusWorkup::set_security_status_workup_groups(const SecurityStatusWorkupGroups& value) { security_status_workup_groups_ = value; }

ServerTcpMessageCode ServerPayloadSecurityStatusWorkup::type() const { return message_type; }

std::string_view ServerPayloadSecurityStatusWorkup::name() const { return "Security Status Workup"; }

std::size_t ServerPayloadSecurityStatusWorkup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 8, length);
    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 8, length);
    md_entry_px_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 2, length);
    trade_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 4, length);
    trade_link_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 1, length);
    workup_trading_status_ = static_cast<WorkupTradingStatus>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 1, length);
    halt_reason_ = static_cast<HaltReason>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ServerPayloadSecurityStatusWorkup", offset + 1, length);
    security_trading_event_ = static_cast<SecurityTradingEvent>(wire::read_u8(data + offset));
    offset += 1;

    offset += security_status_workup_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadSecurityStatusWorkup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadSecurityStatusWorkup", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_i64_le(data + offset, md_entry_px_optional_ex_ ? static_cast<std::int64_t>(md_entry_px_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u16_le(data + offset, trade_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_link_id_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(workup_trading_status_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(halt_reason_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_trading_event_));
    offset += 1;

    offset += security_status_workup_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadSecurityStatusWorkup::encoded_size() const {
    return 8 + 8 + 4 + match_event_indicator_.encoded_size() + 2 + 4 + 1 + 1 + 1 + security_status_workup_groups_.encoded_size();
}

void ServerPayloadSecurityStatusWorkup::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadSecurityStatusWorkup::clone() const {
    return std::make_unique<ServerPayloadSecurityStatusWorkup>(*this);
}

void ServerPayloadSecurityStatusWorkup::print(std::ostream& out) const {
    out << "ServerPayloadSecurityStatusWorkup{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", md_entry_px_optional_ex=";
    print::optional(out, md_entry_px_optional_ex_);
    out << ", security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", trade_date=";
    print::optional(out, trade_date_);
    out << ", trade_link_id=";
    out << trade_link_id_;
    out << ", workup_trading_status=";
    out << workup_trading_status_;
    out << ", halt_reason=";
    out << halt_reason_;
    out << ", security_trading_event=";
    out << security_trading_event_;
    out << ", security_status_workup_groups=";
    security_status_workup_groups_.print(out);
    out << '}';
}

bool ServerPayloadSecurityStatusWorkup::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadSecurityStatusWorkup*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadSecurityStatusWorkup::operator==(const ServerPayloadSecurityStatusWorkup& other) const {
    return transact_time_ == other.transact_time_
        && md_entry_px_optional_ex_ == other.md_entry_px_optional_ex_
        && security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && trade_date_ == other.trade_date_
        && trade_link_id_ == other.trade_link_id_
        && workup_trading_status_ == other.workup_trading_status_
        && halt_reason_ == other.halt_reason_
        && security_trading_event_ == other.security_trading_event_
        && security_status_workup_groups_ == other.security_status_workup_groups_;
}

bool ServerPayloadSecurityStatusWorkup::operator!=(const ServerPayloadSecurityStatusWorkup& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
