#include "SecurityStatus3Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

SecurityStatus3Message::SecurityStatus3Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, SecurityTradingStatus security_trading_status, std::optional<SecurityTradingEvent> security_trading_event, std::uint16_t trade_date, const std::array<std::byte, 2>& offset_14_padding_2, std::optional<std::chrono::nanoseconds> trad_ses_open_time, std::optional<std::uint64_t> transact_time, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), trading_session_id_(trading_session_id), security_trading_status_(security_trading_status), security_trading_event_(security_trading_event), trade_date_(trade_date), offset_14_padding_2_(offset_14_padding_2), trad_ses_open_time_(trad_ses_open_time), transact_time_(transact_time), rpt_seq_(rpt_seq) {}

std::uint64_t SecurityStatus3Message::security_id() const { return security_id_; }
void SecurityStatus3Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& SecurityStatus3Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& SecurityStatus3Message::match_event_indicator() { return match_event_indicator_; }
void SecurityStatus3Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

TradingSessionId SecurityStatus3Message::trading_session_id() const { return trading_session_id_; }
void SecurityStatus3Message::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

SecurityTradingStatus SecurityStatus3Message::security_trading_status() const { return security_trading_status_; }
void SecurityStatus3Message::set_security_trading_status(SecurityTradingStatus value) { security_trading_status_ = value; }

std::optional<SecurityTradingEvent> SecurityStatus3Message::security_trading_event() const { return security_trading_event_; }
void SecurityStatus3Message::set_security_trading_event(std::optional<SecurityTradingEvent> value) { security_trading_event_ = value; }

std::uint16_t SecurityStatus3Message::trade_date() const { return trade_date_; }
void SecurityStatus3Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

const std::array<std::byte, 2>& SecurityStatus3Message::offset_14_padding_2() const { return offset_14_padding_2_; }
std::array<std::byte, 2>& SecurityStatus3Message::offset_14_padding_2() { return offset_14_padding_2_; }
void SecurityStatus3Message::set_offset_14_padding_2(const std::array<std::byte, 2>& value) { offset_14_padding_2_ = value; }

std::optional<std::chrono::nanoseconds> SecurityStatus3Message::trad_ses_open_time() const { return trad_ses_open_time_; }
void SecurityStatus3Message::set_trad_ses_open_time(std::optional<std::chrono::nanoseconds> value) { trad_ses_open_time_ = value; }

std::optional<std::uint64_t> SecurityStatus3Message::transact_time() const { return transact_time_; }
void SecurityStatus3Message::set_transact_time(std::optional<std::uint64_t> value) { transact_time_ = value; }

std::optional<std::uint32_t> SecurityStatus3Message::rpt_seq() const { return rpt_seq_; }
void SecurityStatus3Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode SecurityStatus3Message::type() const { return message_type; }

std::string_view SecurityStatus3Message::name() const { return "Security Status 3 Message"; }

std::size_t SecurityStatus3Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityStatus3Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    trading_session_id_ = static_cast<TradingSessionId>(wire::read_u8(data + offset));
    offset += 1;

    security_trading_status_ = static_cast<SecurityTradingStatus>(wire::read_u8(data + offset));
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

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t SecurityStatus3Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityStatus3Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_trading_status_));
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

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t SecurityStatus3Message::encoded_size() const {
    return wire_size;
}

void SecurityStatus3Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityStatus3Message::clone() const {
    return std::make_unique<SecurityStatus3Message>(*this);
}

void SecurityStatus3Message::print(std::ostream& out) const {
    out << "SecurityStatus3Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", trading_session_id=";
    out << trading_session_id_;
    out << ", security_trading_status=";
    out << security_trading_status_;
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
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool SecurityStatus3Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityStatus3Message*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityStatus3Message::operator==(const SecurityStatus3Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && trading_session_id_ == other.trading_session_id_
        && security_trading_status_ == other.security_trading_status_
        && security_trading_event_ == other.security_trading_event_
        && trade_date_ == other.trade_date_
        && offset_14_padding_2_ == other.offset_14_padding_2_
        && trad_ses_open_time_ == other.trad_ses_open_time_
        && transact_time_ == other.transact_time_
        && rpt_seq_ == other.rpt_seq_;
}

bool SecurityStatus3Message::operator!=(const SecurityStatus3Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
