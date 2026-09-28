#include "LowPrice25Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

LowPrice25Message::LowPrice25Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, std::uint16_t trade_date, Decimal md_future_price, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), md_update_action_(md_update_action), trade_date_(trade_date), md_future_price_(md_future_price), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t LowPrice25Message::security_id() const { return security_id_; }
void LowPrice25Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& LowPrice25Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& LowPrice25Message::match_event_indicator() { return match_event_indicator_; }
void LowPrice25Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

MdUpdateAction LowPrice25Message::md_update_action() const { return md_update_action_; }
void LowPrice25Message::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

std::uint16_t LowPrice25Message::trade_date() const { return trade_date_; }
void LowPrice25Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

Decimal LowPrice25Message::md_future_price() const { return md_future_price_; }
void LowPrice25Message::set_md_future_price(Decimal value) { md_future_price_ = value; }

std::optional<std::chrono::nanoseconds> LowPrice25Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void LowPrice25Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> LowPrice25Message::rpt_seq() const { return rpt_seq_; }
void LowPrice25Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode LowPrice25Message::type() const { return message_type; }

std::string_view LowPrice25Message::name() const { return "Low Price 25 Message"; }

std::size_t LowPrice25Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LowPrice25Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    md_future_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t LowPrice25Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LowPrice25Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_future_price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t LowPrice25Message::encoded_size() const {
    return wire_size;
}

void LowPrice25Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LowPrice25Message::clone() const {
    return std::make_unique<LowPrice25Message>(*this);
}

void LowPrice25Message::print(std::ostream& out) const {
    out << "LowPrice25Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", trade_date=";
    out << trade_date_;
    out << ", md_future_price=";
    out << md_future_price_;
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool LowPrice25Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LowPrice25Message*>(&other);
    return that != nullptr && *this == *that;
}

bool LowPrice25Message::operator==(const LowPrice25Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && md_update_action_ == other.md_update_action_
        && trade_date_ == other.trade_date_
        && md_future_price_ == other.md_future_price_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool LowPrice25Message::operator!=(const LowPrice25Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
