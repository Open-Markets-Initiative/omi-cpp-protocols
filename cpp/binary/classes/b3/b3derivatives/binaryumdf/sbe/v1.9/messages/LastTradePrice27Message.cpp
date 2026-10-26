#include "LastTradePrice27Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

LastTradePrice27Message::LastTradePrice27Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, TradingSessionId trading_session_id, const TradeCondition& trade_condition, Decimal md_future_price, std::int64_t md_entry_size_quantity, std::uint32_t trade_id, std::optional<std::uint32_t> md_entry_buyer, std::optional<std::uint32_t> md_entry_seller, std::uint16_t trade_date, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq, std::optional<std::uint16_t> seller_days, std::optional<Decimal> md_entry_interest_rate, std::optional<TrdSubType> trd_sub_type, const std::array<std::byte, 3>& padding_3)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), trading_session_id_(trading_session_id), trade_condition_(trade_condition), md_future_price_(md_future_price), md_entry_size_quantity_(md_entry_size_quantity), trade_id_(trade_id), md_entry_buyer_(md_entry_buyer), md_entry_seller_(md_entry_seller), trade_date_(trade_date), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq), seller_days_(seller_days), md_entry_interest_rate_(md_entry_interest_rate), trd_sub_type_(trd_sub_type), padding_3_(padding_3) {}

std::uint64_t LastTradePrice27Message::security_id() const { return security_id_; }
void LastTradePrice27Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& LastTradePrice27Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& LastTradePrice27Message::match_event_indicator() { return match_event_indicator_; }
void LastTradePrice27Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

TradingSessionId LastTradePrice27Message::trading_session_id() const { return trading_session_id_; }
void LastTradePrice27Message::set_trading_session_id(TradingSessionId value) { trading_session_id_ = value; }

const TradeCondition& LastTradePrice27Message::trade_condition() const { return trade_condition_; }
TradeCondition& LastTradePrice27Message::trade_condition() { return trade_condition_; }
void LastTradePrice27Message::set_trade_condition(const TradeCondition& value) { trade_condition_ = value; }

Decimal LastTradePrice27Message::md_future_price() const { return md_future_price_; }
void LastTradePrice27Message::set_md_future_price(Decimal value) { md_future_price_ = value; }

std::int64_t LastTradePrice27Message::md_entry_size_quantity() const { return md_entry_size_quantity_; }
void LastTradePrice27Message::set_md_entry_size_quantity(std::int64_t value) { md_entry_size_quantity_ = value; }

std::uint32_t LastTradePrice27Message::trade_id() const { return trade_id_; }
void LastTradePrice27Message::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::optional<std::uint32_t> LastTradePrice27Message::md_entry_buyer() const { return md_entry_buyer_; }
void LastTradePrice27Message::set_md_entry_buyer(std::optional<std::uint32_t> value) { md_entry_buyer_ = value; }

std::optional<std::uint32_t> LastTradePrice27Message::md_entry_seller() const { return md_entry_seller_; }
void LastTradePrice27Message::set_md_entry_seller(std::optional<std::uint32_t> value) { md_entry_seller_ = value; }

std::uint16_t LastTradePrice27Message::trade_date() const { return trade_date_; }
void LastTradePrice27Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::optional<std::chrono::nanoseconds> LastTradePrice27Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void LastTradePrice27Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> LastTradePrice27Message::rpt_seq() const { return rpt_seq_; }
void LastTradePrice27Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

std::optional<std::uint16_t> LastTradePrice27Message::seller_days() const { return seller_days_; }
void LastTradePrice27Message::set_seller_days(std::optional<std::uint16_t> value) { seller_days_ = value; }

std::optional<Decimal> LastTradePrice27Message::md_entry_interest_rate() const { return md_entry_interest_rate_; }
void LastTradePrice27Message::set_md_entry_interest_rate(std::optional<Decimal> value) { md_entry_interest_rate_ = value; }

std::optional<TrdSubType> LastTradePrice27Message::trd_sub_type() const { return trd_sub_type_; }
void LastTradePrice27Message::set_trd_sub_type(std::optional<TrdSubType> value) { trd_sub_type_ = value; }

const std::array<std::byte, 3>& LastTradePrice27Message::padding_3() const { return padding_3_; }
std::array<std::byte, 3>& LastTradePrice27Message::padding_3() { return padding_3_; }
void LastTradePrice27Message::set_padding_3(const std::array<std::byte, 3>& value) { padding_3_ = value; }

MessageCode LastTradePrice27Message::type() const { return message_type; }

std::string_view LastTradePrice27Message::name() const { return "Last Trade Price 27 Message"; }

std::size_t LastTradePrice27Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LastTradePrice27Message", wire_size, length);

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

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    seller_days_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    md_entry_interest_rate_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(0LL), -4);
    offset += 8;

    trd_sub_type_ = wire::nullable_enum<TrdSubType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::read_bytes(data + offset, padding_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t LastTradePrice27Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LastTradePrice27Message", wire_size, capacity);

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

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u16_le(data + offset, seller_days_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_i64_le(data + offset, md_entry_interest_rate_ ? static_cast<std::int64_t>(md_entry_interest_rate_->mantissa()) : static_cast<std::int64_t>(0LL));
    offset += 8;

    wire::write_u8(data + offset, trd_sub_type_ ? static_cast<std::uint8_t>(*trd_sub_type_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_bytes(data + offset, padding_3_.data(), 3);
    offset += 3;

    return offset;
}

std::size_t LastTradePrice27Message::encoded_size() const {
    return wire_size;
}

void LastTradePrice27Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LastTradePrice27Message::clone() const {
    return std::make_unique<LastTradePrice27Message>(*this);
}

void LastTradePrice27Message::print(std::ostream& out) const {
    out << "LastTradePrice27Message{";
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
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << ", seller_days=";
    print::optional(out, seller_days_);
    out << ", md_entry_interest_rate=";
    print::optional(out, md_entry_interest_rate_);
    out << ", trd_sub_type=";
    print::optional(out, trd_sub_type_);
    out << ", padding_3=";
    print::hex(out, padding_3_.data(), padding_3_.size());
    out << '}';
}

bool LastTradePrice27Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LastTradePrice27Message*>(&other);
    return that != nullptr && *this == *that;
}

bool LastTradePrice27Message::operator==(const LastTradePrice27Message& other) const {
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
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_
        && seller_days_ == other.seller_days_
        && md_entry_interest_rate_ == other.md_entry_interest_rate_
        && trd_sub_type_ == other.trd_sub_type_
        && padding_3_ == other.padding_3_;
}

bool LastTradePrice27Message::operator!=(const LastTradePrice27Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
