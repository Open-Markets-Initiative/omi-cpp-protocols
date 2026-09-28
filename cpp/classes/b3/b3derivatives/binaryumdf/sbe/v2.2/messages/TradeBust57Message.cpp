#include "TradeBust57Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

TradeBust57Message::TradeBust57Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, const std::array<std::byte, 2>& offset_10_padding_2, Decimal md_future_price, std::int64_t md_entry_size_quantity, std::uint32_t trade_id, std::uint16_t trade_date, const std::array<std::byte, 2>& offset_34_padding_2, std::optional<std::uint64_t> transact_time, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), trading_session_id_(trading_session_id), offset_10_padding_2_(offset_10_padding_2), md_future_price_(md_future_price), md_entry_size_quantity_(md_entry_size_quantity), trade_id_(trade_id), trade_date_(trade_date), offset_34_padding_2_(offset_34_padding_2), transact_time_(transact_time), rpt_seq_(rpt_seq) {}

std::uint64_t TradeBust57Message::security_id() const { return security_id_; }
void TradeBust57Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& TradeBust57Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& TradeBust57Message::match_event_indicator() { return match_event_indicator_; }
void TradeBust57Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

TradingSessionId TradeBust57Message::trading_session_id() const { return trading_session_id_; }
void TradeBust57Message::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

const std::array<std::byte, 2>& TradeBust57Message::offset_10_padding_2() const { return offset_10_padding_2_; }
std::array<std::byte, 2>& TradeBust57Message::offset_10_padding_2() { return offset_10_padding_2_; }
void TradeBust57Message::set_offset_10_padding_2(const std::array<std::byte, 2>& value) { offset_10_padding_2_ = value; }

Decimal TradeBust57Message::md_future_price() const { return md_future_price_; }
void TradeBust57Message::set_md_future_price(Decimal value) { md_future_price_ = value; }

std::int64_t TradeBust57Message::md_entry_size_quantity() const { return md_entry_size_quantity_; }
void TradeBust57Message::set_md_entry_size_quantity(std::int64_t value) { md_entry_size_quantity_ = value; }

std::uint32_t TradeBust57Message::trade_id() const { return trade_id_; }
void TradeBust57Message::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::uint16_t TradeBust57Message::trade_date() const { return trade_date_; }
void TradeBust57Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

const std::array<std::byte, 2>& TradeBust57Message::offset_34_padding_2() const { return offset_34_padding_2_; }
std::array<std::byte, 2>& TradeBust57Message::offset_34_padding_2() { return offset_34_padding_2_; }
void TradeBust57Message::set_offset_34_padding_2(const std::array<std::byte, 2>& value) { offset_34_padding_2_ = value; }

std::optional<std::uint64_t> TradeBust57Message::transact_time() const { return transact_time_; }
void TradeBust57Message::set_transact_time(std::optional<std::uint64_t> value) { transact_time_ = value; }

std::optional<std::uint32_t> TradeBust57Message::rpt_seq() const { return rpt_seq_; }
void TradeBust57Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode TradeBust57Message::type() const { return message_type; }

std::string_view TradeBust57Message::name() const { return "Trade Bust 57 Message"; }

std::size_t TradeBust57Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeBust57Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    trading_session_id_ = static_cast<TradingSessionId>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_10_padding_2_.data(), 2);
    offset += 2;

    md_future_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    md_entry_size_quantity_ = wire::read_i64_le(data + offset);
    offset += 8;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, offset_34_padding_2_.data(), 2);
    offset += 2;

    transact_time_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t TradeBust57Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeBust57Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    wire::write_bytes(data + offset, offset_10_padding_2_.data(), 2);
    offset += 2;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_future_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_size_quantity_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_bytes(data + offset, offset_34_padding_2_.data(), 2);
    offset += 2;

    wire::write_u64_le(data + offset, transact_time_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t TradeBust57Message::encoded_size() const {
    return wire_size;
}

void TradeBust57Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeBust57Message::clone() const {
    return std::make_unique<TradeBust57Message>(*this);
}

void TradeBust57Message::print(std::ostream& out) const {
    out << "TradeBust57Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", trading_session_id=";
    out << trading_session_id_;
    out << ", offset_10_padding_2=";
    print::hex(out, offset_10_padding_2_.data(), offset_10_padding_2_.size());
    out << ", md_future_price=";
    out << md_future_price_;
    out << ", md_entry_size_quantity=";
    out << md_entry_size_quantity_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", trade_date=";
    out << trade_date_;
    out << ", offset_34_padding_2=";
    print::hex(out, offset_34_padding_2_.data(), offset_34_padding_2_.size());
    out << ", transact_time=";
    print::optional(out, transact_time_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool TradeBust57Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeBust57Message*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeBust57Message::operator==(const TradeBust57Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && trading_session_id_ == other.trading_session_id_
        && offset_10_padding_2_ == other.offset_10_padding_2_
        && md_future_price_ == other.md_future_price_
        && md_entry_size_quantity_ == other.md_entry_size_quantity_
        && trade_id_ == other.trade_id_
        && trade_date_ == other.trade_date_
        && offset_34_padding_2_ == other.offset_34_padding_2_
        && transact_time_ == other.transact_time_
        && rpt_seq_ == other.rpt_seq_;
}

bool TradeBust57Message::operator!=(const TradeBust57Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
