#include "SettlementPrice28Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

SettlementPrice28Message::SettlementPrice28Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 1>& offset_9_padding_1, std::uint16_t trade_date, Decimal md_future_price, std::optional<std::chrono::nanoseconds> md_entry_timestamp, OpenCloseSettlFlag open_close_settl_flag, PriceType price_type, SettlPriceType settl_price_type, std::optional<std::uint32_t> rpt_seq, const std::array<std::byte, 1>& padding_1)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), offset_9_padding_1_(offset_9_padding_1), trade_date_(trade_date), md_future_price_(md_future_price), md_entry_timestamp_(md_entry_timestamp), open_close_settl_flag_(open_close_settl_flag), price_type_(price_type), settl_price_type_(settl_price_type), rpt_seq_(rpt_seq), padding_1_(padding_1) {}

std::uint64_t SettlementPrice28Message::security_id() const { return security_id_; }
void SettlementPrice28Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& SettlementPrice28Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& SettlementPrice28Message::match_event_indicator() { return match_event_indicator_; }
void SettlementPrice28Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 1>& SettlementPrice28Message::offset_9_padding_1() const { return offset_9_padding_1_; }
std::array<std::byte, 1>& SettlementPrice28Message::offset_9_padding_1() { return offset_9_padding_1_; }
void SettlementPrice28Message::set_offset_9_padding_1(const std::array<std::byte, 1>& value) { offset_9_padding_1_ = value; }

std::uint16_t SettlementPrice28Message::trade_date() const { return trade_date_; }
void SettlementPrice28Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

Decimal SettlementPrice28Message::md_future_price() const { return md_future_price_; }
void SettlementPrice28Message::set_md_future_price(Decimal value) { md_future_price_ = value; }

std::optional<std::chrono::nanoseconds> SettlementPrice28Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void SettlementPrice28Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

OpenCloseSettlFlag SettlementPrice28Message::open_close_settl_flag() const { return open_close_settl_flag_; }
void SettlementPrice28Message::set_open_close_settl_flag(OpenCloseSettlFlag value) { open_close_settl_flag_ = value; }

PriceType SettlementPrice28Message::price_type() const { return price_type_; }
void SettlementPrice28Message::set_price_type(PriceType value) { price_type_ = value; }

SettlPriceType SettlementPrice28Message::settl_price_type() const { return settl_price_type_; }
void SettlementPrice28Message::set_settl_price_type(SettlPriceType value) { settl_price_type_ = value; }

std::optional<std::uint32_t> SettlementPrice28Message::rpt_seq() const { return rpt_seq_; }
void SettlementPrice28Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

const std::array<std::byte, 1>& SettlementPrice28Message::padding_1() const { return padding_1_; }
std::array<std::byte, 1>& SettlementPrice28Message::padding_1() { return padding_1_; }
void SettlementPrice28Message::set_padding_1(const std::array<std::byte, 1>& value) { padding_1_ = value; }

MessageCode SettlementPrice28Message::type() const { return message_type; }

std::string_view SettlementPrice28Message::name() const { return "Settlement Price 28 Message"; }

std::size_t SettlementPrice28Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SettlementPrice28Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, offset_9_padding_1_.data(), 1);
    offset += 1;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    md_future_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    open_close_settl_flag_ = static_cast<OpenCloseSettlFlag>(wire::read_u8(data + offset));
    offset += 1;

    price_type_ = static_cast<PriceType>(wire::read_u8(data + offset));
    offset += 1;

    settl_price_type_ = static_cast<SettlPriceType>(wire::read_u8(data + offset));
    offset += 1;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::read_bytes(data + offset, padding_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t SettlementPrice28Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SettlementPrice28Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_9_padding_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_future_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(open_close_settl_flag_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(settl_price_type_));
    offset += 1;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_bytes(data + offset, padding_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t SettlementPrice28Message::encoded_size() const {
    return wire_size;
}

void SettlementPrice28Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SettlementPrice28Message::clone() const {
    return std::make_unique<SettlementPrice28Message>(*this);
}

void SettlementPrice28Message::print(std::ostream& out) const {
    out << "SettlementPrice28Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", offset_9_padding_1=";
    print::hex(out, offset_9_padding_1_.data(), offset_9_padding_1_.size());
    out << ", trade_date=";
    out << trade_date_;
    out << ", md_future_price=";
    out << md_future_price_;
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", open_close_settl_flag=";
    out << open_close_settl_flag_;
    out << ", price_type=";
    out << price_type_;
    out << ", settl_price_type=";
    out << settl_price_type_;
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << ", padding_1=";
    print::hex(out, padding_1_.data(), padding_1_.size());
    out << '}';
}

bool SettlementPrice28Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SettlementPrice28Message*>(&other);
    return that != nullptr && *this == *that;
}

bool SettlementPrice28Message::operator==(const SettlementPrice28Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && offset_9_padding_1_ == other.offset_9_padding_1_
        && trade_date_ == other.trade_date_
        && md_future_price_ == other.md_future_price_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && open_close_settl_flag_ == other.open_close_settl_flag_
        && price_type_ == other.price_type_
        && settl_price_type_ == other.settl_price_type_
        && rpt_seq_ == other.rpt_seq_
        && padding_1_ == other.padding_1_;
}

bool SettlementPrice28Message::operator!=(const SettlementPrice28Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
