#include "ServerPayloadSecurityStatus.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

ServerPayloadSecurityStatus::ServerPayloadSecurityStatus(std::chrono::nanoseconds transact_time, const std::string& security_group, const std::string& asset, std::optional<std::int32_t> security_id_optional, std::optional<std::uint16_t> trade_date, const MatchEventIndicator& match_event_indicator, std::optional<SecurityTradingStatus> security_trading_status, HaltReason halt_reason, SecurityTradingEvent security_trading_event)
  : transact_time_(transact_time), security_group_(security_group), asset_(asset), security_id_optional_(security_id_optional), trade_date_(trade_date), match_event_indicator_(match_event_indicator), security_trading_status_(security_trading_status), halt_reason_(halt_reason), security_trading_event_(security_trading_event) {}

std::chrono::nanoseconds ServerPayloadSecurityStatus::transact_time() const { return transact_time_; }
void ServerPayloadSecurityStatus::set_transact_time(std::chrono::nanoseconds value) { transact_time_ = value; }

const std::string& ServerPayloadSecurityStatus::security_group() const { return security_group_; }
std::string& ServerPayloadSecurityStatus::security_group() { return security_group_; }
void ServerPayloadSecurityStatus::set_security_group(const std::string& value) { security_group_ = value; }

const std::string& ServerPayloadSecurityStatus::asset() const { return asset_; }
std::string& ServerPayloadSecurityStatus::asset() { return asset_; }
void ServerPayloadSecurityStatus::set_asset(const std::string& value) { asset_ = value; }

std::optional<std::int32_t> ServerPayloadSecurityStatus::security_id_optional() const { return security_id_optional_; }
void ServerPayloadSecurityStatus::set_security_id_optional(std::optional<std::int32_t> value) { security_id_optional_ = value; }

std::optional<std::uint16_t> ServerPayloadSecurityStatus::trade_date() const { return trade_date_; }
void ServerPayloadSecurityStatus::set_trade_date(std::optional<std::uint16_t> value) { trade_date_ = value; }

const MatchEventIndicator& ServerPayloadSecurityStatus::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadSecurityStatus::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadSecurityStatus::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<SecurityTradingStatus> ServerPayloadSecurityStatus::security_trading_status() const { return security_trading_status_; }
void ServerPayloadSecurityStatus::set_security_trading_status(std::optional<SecurityTradingStatus> value) { security_trading_status_ = value; }

HaltReason ServerPayloadSecurityStatus::halt_reason() const { return halt_reason_; }
void ServerPayloadSecurityStatus::set_halt_reason(HaltReason value) { halt_reason_ = value; }

SecurityTradingEvent ServerPayloadSecurityStatus::security_trading_event() const { return security_trading_event_; }
void ServerPayloadSecurityStatus::set_security_trading_event(SecurityTradingEvent value) { security_trading_event_ = value; }

ServerTcpMessageCode ServerPayloadSecurityStatus::type() const { return message_type; }

std::string_view ServerPayloadSecurityStatus::name() const { return "Security Status"; }

std::size_t ServerPayloadSecurityStatus::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerPayloadSecurityStatus", wire_size, length);

    transact_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    security_group_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    security_id_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    trade_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    security_trading_status_ = wire::nullable_enum<SecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    halt_reason_ = static_cast<HaltReason>(wire::read_u8(data + offset));
    offset += 1;

    security_trading_event_ = static_cast<SecurityTradingEvent>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t ServerPayloadSecurityStatus::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadSecurityStatus", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(transact_time_.count()));
    offset += 8;

    wire::write_text(data + offset, 6, '\0', security_group_);
    offset += 6;

    wire::write_text(data + offset, 6, '\0', asset_);
    offset += 6;

    wire::write_i32_le(data + offset, security_id_optional_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_u16_le(data + offset, trade_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, security_trading_status_ ? static_cast<std::uint8_t>(*security_trading_status_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(halt_reason_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_trading_event_));
    offset += 1;

    return offset;
}

std::size_t ServerPayloadSecurityStatus::encoded_size() const {
    return wire_size;
}

void ServerPayloadSecurityStatus::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadSecurityStatus::clone() const {
    return std::make_unique<ServerPayloadSecurityStatus>(*this);
}

void ServerPayloadSecurityStatus::print(std::ostream& out) const {
    out << "ServerPayloadSecurityStatus{";
    out << "transact_time=";
    out << transact_time_.count();
    out << ", security_group=";
    print::text(out, security_group_);
    out << ", asset=";
    print::text(out, asset_);
    out << ", security_id_optional=";
    print::optional(out, security_id_optional_);
    out << ", trade_date=";
    print::optional(out, trade_date_);
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", security_trading_status=";
    print::optional(out, security_trading_status_);
    out << ", halt_reason=";
    out << halt_reason_;
    out << ", security_trading_event=";
    out << security_trading_event_;
    out << '}';
}

bool ServerPayloadSecurityStatus::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadSecurityStatus*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadSecurityStatus::operator==(const ServerPayloadSecurityStatus& other) const {
    return transact_time_ == other.transact_time_
        && security_group_ == other.security_group_
        && asset_ == other.asset_
        && security_id_optional_ == other.security_id_optional_
        && trade_date_ == other.trade_date_
        && match_event_indicator_ == other.match_event_indicator_
        && security_trading_status_ == other.security_trading_status_
        && halt_reason_ == other.halt_reason_
        && security_trading_event_ == other.security_trading_event_;
}

bool ServerPayloadSecurityStatus::operator!=(const ServerPayloadSecurityStatus& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
