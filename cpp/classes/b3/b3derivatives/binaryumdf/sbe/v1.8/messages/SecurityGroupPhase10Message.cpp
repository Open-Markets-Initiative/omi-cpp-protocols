#include "SecurityGroupPhase10Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

SecurityGroupPhase10Message::SecurityGroupPhase10Message(const std::string& security_group, const std::array<std::byte, 5>& offset_3_padding_5, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, TradingSessionSubId trading_session_sub_id, std::optional<SecurityTradingEvent> security_trading_event, std::uint16_t trade_date, const std::array<std::byte, 2>& offset_14_padding_2, std::optional<std::chrono::nanoseconds> trad_ses_open_time, std::optional<std::uint64_t> transact_time)
  : security_group_(security_group), offset_3_padding_5_(offset_3_padding_5), match_event_indicator_(match_event_indicator), trading_session_id_(trading_session_id), trading_session_sub_id_(trading_session_sub_id), security_trading_event_(security_trading_event), trade_date_(trade_date), offset_14_padding_2_(offset_14_padding_2), trad_ses_open_time_(trad_ses_open_time), transact_time_(transact_time) {}

const std::string& SecurityGroupPhase10Message::security_group() const { return security_group_; }
std::string& SecurityGroupPhase10Message::security_group() { return security_group_; }
void SecurityGroupPhase10Message::set_security_group(const std::string& value) { security_group_ = value; }

const std::array<std::byte, 5>& SecurityGroupPhase10Message::offset_3_padding_5() const { return offset_3_padding_5_; }
std::array<std::byte, 5>& SecurityGroupPhase10Message::offset_3_padding_5() { return offset_3_padding_5_; }
void SecurityGroupPhase10Message::set_offset_3_padding_5(const std::array<std::byte, 5>& value) { offset_3_padding_5_ = value; }

const MatchEventIndicator& SecurityGroupPhase10Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& SecurityGroupPhase10Message::match_event_indicator() { return match_event_indicator_; }
void SecurityGroupPhase10Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

TradingSessionId SecurityGroupPhase10Message::trading_session_id() const { return trading_session_id_; }
void SecurityGroupPhase10Message::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

TradingSessionSubId SecurityGroupPhase10Message::trading_session_sub_id() const { return trading_session_sub_id_; }
void SecurityGroupPhase10Message::set_trading_session_sub_id(TradingSessionSubId value) { trading_session_sub_id_ = value; }

std::optional<SecurityTradingEvent> SecurityGroupPhase10Message::security_trading_event() const { return security_trading_event_; }
void SecurityGroupPhase10Message::set_security_trading_event(std::optional<SecurityTradingEvent> value) { security_trading_event_ = value; }

std::uint16_t SecurityGroupPhase10Message::trade_date() const { return trade_date_; }
void SecurityGroupPhase10Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

const std::array<std::byte, 2>& SecurityGroupPhase10Message::offset_14_padding_2() const { return offset_14_padding_2_; }
std::array<std::byte, 2>& SecurityGroupPhase10Message::offset_14_padding_2() { return offset_14_padding_2_; }
void SecurityGroupPhase10Message::set_offset_14_padding_2(const std::array<std::byte, 2>& value) { offset_14_padding_2_ = value; }

std::optional<std::chrono::nanoseconds> SecurityGroupPhase10Message::trad_ses_open_time() const { return trad_ses_open_time_; }
void SecurityGroupPhase10Message::set_trad_ses_open_time(std::optional<std::chrono::nanoseconds> value) { trad_ses_open_time_ = value; }

std::optional<std::uint64_t> SecurityGroupPhase10Message::transact_time() const { return transact_time_; }
void SecurityGroupPhase10Message::set_transact_time(std::optional<std::uint64_t> value) { transact_time_ = value; }

MessageCode SecurityGroupPhase10Message::type() const { return message_type; }

std::string_view SecurityGroupPhase10Message::name() const { return "Security Group Phase 10 Message"; }

std::size_t SecurityGroupPhase10Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityGroupPhase10Message", wire_size, length);

    security_group_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::read_bytes(data + offset, offset_3_padding_5_.data(), 5);
    offset += 5;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    trading_session_id_ = static_cast<TradingSessionId>(wire::read_u8(data + offset));
    offset += 1;

    trading_session_sub_id_ = static_cast<TradingSessionSubId>(wire::read_u8(data + offset));
    offset += 1;

    security_trading_event_ = wire::nullable_enum<SecurityTradingEvent>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, offset_14_padding_2_.data(), 2);
    offset += 2;

    trad_ses_open_time_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    transact_time_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t SecurityGroupPhase10Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityGroupPhase10Message", wire_size, capacity);

    wire::write_text(data + offset, 3, '\0', security_group_);
    offset += 3;

    wire::write_bytes(data + offset, offset_3_padding_5_.data(), 5);
    offset += 5;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_sub_id_));
    offset += 1;

    wire::write_u8(data + offset, security_trading_event_ ? static_cast<std::uint8_t>(*security_trading_event_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_bytes(data + offset, offset_14_padding_2_.data(), 2);
    offset += 2;

    wire::write_u64_le(data + offset, trad_ses_open_time_ ? static_cast<std::uint64_t>(trad_ses_open_time_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u64_le(data + offset, transact_time_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    return offset;
}

std::size_t SecurityGroupPhase10Message::encoded_size() const {
    return wire_size;
}

void SecurityGroupPhase10Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityGroupPhase10Message::clone() const {
    return std::make_unique<SecurityGroupPhase10Message>(*this);
}

void SecurityGroupPhase10Message::print(std::ostream& out) const {
    out << "SecurityGroupPhase10Message{";
    out << "security_group=";
    print::text(out, security_group_);
    out << ", offset_3_padding_5=";
    print::hex(out, offset_3_padding_5_.data(), offset_3_padding_5_.size());
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", trading_session_id=";
    out << trading_session_id_;
    out << ", trading_session_sub_id=";
    out << trading_session_sub_id_;
    out << ", security_trading_event=";
    print::optional(out, security_trading_event_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", offset_14_padding_2=";
    print::hex(out, offset_14_padding_2_.data(), offset_14_padding_2_.size());
    out << ", trad_ses_open_time=";
    print::optional_duration(out, trad_ses_open_time_);
    out << ", transact_time=";
    print::optional(out, transact_time_);
    out << '}';
}

bool SecurityGroupPhase10Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityGroupPhase10Message*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityGroupPhase10Message::operator==(const SecurityGroupPhase10Message& other) const {
    return security_group_ == other.security_group_
        && offset_3_padding_5_ == other.offset_3_padding_5_
        && match_event_indicator_ == other.match_event_indicator_
        && trading_session_id_ == other.trading_session_id_
        && trading_session_sub_id_ == other.trading_session_sub_id_
        && security_trading_event_ == other.security_trading_event_
        && trade_date_ == other.trade_date_
        && offset_14_padding_2_ == other.offset_14_padding_2_
        && trad_ses_open_time_ == other.trad_ses_open_time_
        && transact_time_ == other.transact_time_;
}

bool SecurityGroupPhase10Message::operator!=(const SecurityGroupPhase10Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
