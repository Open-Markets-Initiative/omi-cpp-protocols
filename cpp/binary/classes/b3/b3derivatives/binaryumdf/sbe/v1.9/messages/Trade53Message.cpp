#include "Trade53Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

Trade53Message::Trade53Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, const TradeCondition& trade_condition, Decimal md_future_price, std::int64_t md_entry_size_quantity, std::uint32_t trade_id, std::optional<std::uint32_t> md_entry_buyer, std::optional<std::uint32_t> md_entry_seller, std::uint16_t trade_date, std::optional<TrdSubType> trd_sub_type, const std::array<std::byte, 1>& offset_43_padding_1, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), trading_session_id_(trading_session_id), trade_condition_(trade_condition), md_future_price_(md_future_price), md_entry_size_quantity_(md_entry_size_quantity), trade_id_(trade_id), md_entry_buyer_(md_entry_buyer), md_entry_seller_(md_entry_seller), trade_date_(trade_date), trd_sub_type_(trd_sub_type), offset_43_padding_1_(offset_43_padding_1), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t Trade53Message::security_id() const { return security_id_; }
void Trade53Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& Trade53Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& Trade53Message::match_event_indicator() { return match_event_indicator_; }
void Trade53Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

TradingSessionId Trade53Message::trading_session_id() const { return trading_session_id_; }
void Trade53Message::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

const TradeCondition& Trade53Message::trade_condition() const { return trade_condition_; }
TradeCondition& Trade53Message::trade_condition() { return trade_condition_; }
void Trade53Message::set_trade_condition(const TradeCondition& value) { trade_condition_ = value; }

Decimal Trade53Message::md_future_price() const { return md_future_price_; }
void Trade53Message::set_md_future_price(Decimal value) { md_future_price_ = value; }

std::int64_t Trade53Message::md_entry_size_quantity() const { return md_entry_size_quantity_; }
void Trade53Message::set_md_entry_size_quantity(std::int64_t value) { md_entry_size_quantity_ = value; }

std::uint32_t Trade53Message::trade_id() const { return trade_id_; }
void Trade53Message::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::optional<std::uint32_t> Trade53Message::md_entry_buyer() const { return md_entry_buyer_; }
void Trade53Message::set_md_entry_buyer(std::optional<std::uint32_t> value) { md_entry_buyer_ = value; }

std::optional<std::uint32_t> Trade53Message::md_entry_seller() const { return md_entry_seller_; }
void Trade53Message::set_md_entry_seller(std::optional<std::uint32_t> value) { md_entry_seller_ = value; }

std::uint16_t Trade53Message::trade_date() const { return trade_date_; }
void Trade53Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::optional<TrdSubType> Trade53Message::trd_sub_type() const { return trd_sub_type_; }
void Trade53Message::set_trd_sub_type(std::optional<TrdSubType> value) { trd_sub_type_ = value; }

const std::array<std::byte, 1>& Trade53Message::offset_43_padding_1() const { return offset_43_padding_1_; }
std::array<std::byte, 1>& Trade53Message::offset_43_padding_1() { return offset_43_padding_1_; }
void Trade53Message::set_offset_43_padding_1(const std::array<std::byte, 1>& value) { offset_43_padding_1_ = value; }

std::optional<std::chrono::nanoseconds> Trade53Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void Trade53Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> Trade53Message::rpt_seq() const { return rpt_seq_; }
void Trade53Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode Trade53Message::type() const { return message_type; }

std::string_view Trade53Message::name() const { return "Trade 53 Message"; }

std::size_t Trade53Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Trade53Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    trading_session_id_ = static_cast<TradingSessionId>(wire::read_u8(data + offset));
    offset += 1;

    offset += trade_condition_.decode(data + offset, length - offset);

    md_future_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    md_entry_size_quantity_ = wire::read_i64_le(data + offset);
    offset += 8;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    md_entry_buyer_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    md_entry_seller_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    trd_sub_type_ = wire::nullable_enum<TrdSubType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::read_bytes(data + offset, offset_43_padding_1_.data(), 1);
    offset += 1;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t Trade53Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Trade53Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(trading_session_id_));
    offset += 1;

    offset += trade_condition_.encode(data + offset, capacity - offset);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_future_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_size_quantity_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_u32_le(data + offset, md_entry_buyer_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u32_le(data + offset, md_entry_seller_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u8(data + offset, trd_sub_type_ ? static_cast<std::uint8_t>(*trd_sub_type_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_bytes(data + offset, offset_43_padding_1_.data(), 1);
    offset += 1;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t Trade53Message::encoded_size() const {
    return wire_size;
}

void Trade53Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> Trade53Message::clone() const {
    return std::make_unique<Trade53Message>(*this);
}

void Trade53Message::print(std::ostream& out) const {
    out << "Trade53Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", trading_session_id=";
    out << trading_session_id_;
    out << ", trade_condition=";
    trade_condition_.print(out);
    out << ", md_future_price=";
    out << md_future_price_;
    out << ", md_entry_size_quantity=";
    out << md_entry_size_quantity_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", md_entry_buyer=";
    print::optional(out, md_entry_buyer_);
    out << ", md_entry_seller=";
    print::optional(out, md_entry_seller_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", trd_sub_type=";
    print::optional(out, trd_sub_type_);
    out << ", offset_43_padding_1=";
    print::hex(out, offset_43_padding_1_.data(), offset_43_padding_1_.size());
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool Trade53Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const Trade53Message*>(&other);
    return that != nullptr && *this == *that;
}

bool Trade53Message::operator==(const Trade53Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && trading_session_id_ == other.trading_session_id_
        && trade_condition_ == other.trade_condition_
        && md_future_price_ == other.md_future_price_
        && md_entry_size_quantity_ == other.md_entry_size_quantity_
        && trade_id_ == other.trade_id_
        && md_entry_buyer_ == other.md_entry_buyer_
        && md_entry_seller_ == other.md_entry_seller_
        && trade_date_ == other.trade_date_
        && trd_sub_type_ == other.trd_sub_type_
        && offset_43_padding_1_ == other.offset_43_padding_1_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool Trade53Message::operator!=(const Trade53Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
