#include "ExecutionStatistics56Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

ExecutionStatistics56Message::ExecutionStatistics56Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, std::uint16_t trade_date, std::int64_t trade_volume, std::optional<Decimal> vwap_px, std::optional<Decimal> net_chg_prev_day, std::uint32_t number_of_trades, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), trading_session_id_(trading_session_id), trade_date_(trade_date), trade_volume_(trade_volume), vwap_px_(vwap_px), net_chg_prev_day_(net_chg_prev_day), number_of_trades_(number_of_trades), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t ExecutionStatistics56Message::security_id() const { return security_id_; }
void ExecutionStatistics56Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& ExecutionStatistics56Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ExecutionStatistics56Message::match_event_indicator() { return match_event_indicator_; }
void ExecutionStatistics56Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

TradingSessionId ExecutionStatistics56Message::trading_session_id() const { return trading_session_id_; }
void ExecutionStatistics56Message::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

std::uint16_t ExecutionStatistics56Message::trade_date() const { return trade_date_; }
void ExecutionStatistics56Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::int64_t ExecutionStatistics56Message::trade_volume() const { return trade_volume_; }
void ExecutionStatistics56Message::set_trade_volume(std::int64_t value) { trade_volume_ = value; }

std::optional<Decimal> ExecutionStatistics56Message::vwap_px() const { return vwap_px_; }
void ExecutionStatistics56Message::set_vwap_px(std::optional<Decimal> value) { vwap_px_ = value; }

std::optional<Decimal> ExecutionStatistics56Message::net_chg_prev_day() const { return net_chg_prev_day_; }
void ExecutionStatistics56Message::set_net_chg_prev_day(std::optional<Decimal> value) { net_chg_prev_day_ = value; }

std::uint32_t ExecutionStatistics56Message::number_of_trades() const { return number_of_trades_; }
void ExecutionStatistics56Message::set_number_of_trades(std::uint32_t value) { number_of_trades_ = value; }

std::optional<std::chrono::nanoseconds> ExecutionStatistics56Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void ExecutionStatistics56Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> ExecutionStatistics56Message::rpt_seq() const { return rpt_seq_; }
void ExecutionStatistics56Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode ExecutionStatistics56Message::type() const { return message_type; }

std::string_view ExecutionStatistics56Message::name() const { return "Execution Statistics 56 Message"; }

std::size_t ExecutionStatistics56Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ExecutionStatistics56Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    trading_session_id_ = static_cast<TradingSessionId>(wire::read_u8(data + offset));
    offset += 1;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    trade_volume_ = wire::read_i64_le(data + offset);
    offset += 8;

    vwap_px_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    net_chg_prev_day_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    number_of_trades_ = wire::read_u32_le(data + offset);
    offset += 4;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t ExecutionStatistics56Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ExecutionStatistics56Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(trade_volume_));
    offset += 8;

    wire::write_i64_le(data + offset, vwap_px_ ? static_cast<std::int64_t>(vwap_px_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, net_chg_prev_day_ ? static_cast<std::int64_t>(net_chg_prev_day_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(number_of_trades_));
    offset += 4;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t ExecutionStatistics56Message::encoded_size() const {
    return wire_size;
}

void ExecutionStatistics56Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ExecutionStatistics56Message::clone() const {
    return std::make_unique<ExecutionStatistics56Message>(*this);
}

void ExecutionStatistics56Message::print(std::ostream& out) const {
    out << "ExecutionStatistics56Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", trading_session_id=";
    out << trading_session_id_;
    out << ", trade_date=";
    out << trade_date_;
    out << ", trade_volume=";
    out << trade_volume_;
    out << ", vwap_px=";
    print::optional(out, vwap_px_);
    out << ", net_chg_prev_day=";
    print::optional(out, net_chg_prev_day_);
    out << ", number_of_trades=";
    out << number_of_trades_;
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool ExecutionStatistics56Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ExecutionStatistics56Message*>(&other);
    return that != nullptr && *this == *that;
}

bool ExecutionStatistics56Message::operator==(const ExecutionStatistics56Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && trading_session_id_ == other.trading_session_id_
        && trade_date_ == other.trade_date_
        && trade_volume_ == other.trade_volume_
        && vwap_px_ == other.vwap_px_
        && net_chg_prev_day_ == other.net_chg_prev_day_
        && number_of_trades_ == other.number_of_trades_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool ExecutionStatistics56Message::operator!=(const ExecutionStatistics56Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
