#include "TheoreticalOpeningPrice16Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

TheoreticalOpeningPrice16Message::TheoreticalOpeningPrice16Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, std::uint16_t trade_date, std::optional<Decimal> md_corporate_offset_price_optional, std::optional<std::int64_t> md_entry_size_quantity_optional, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), md_update_action_(md_update_action), trade_date_(trade_date), md_corporate_offset_price_optional_(md_corporate_offset_price_optional), md_entry_size_quantity_optional_(md_entry_size_quantity_optional), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t TheoreticalOpeningPrice16Message::security_id() const { return security_id_; }
void TheoreticalOpeningPrice16Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& TheoreticalOpeningPrice16Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& TheoreticalOpeningPrice16Message::match_event_indicator() { return match_event_indicator_; }
void TheoreticalOpeningPrice16Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

MdUpdateAction TheoreticalOpeningPrice16Message::md_update_action() const { return md_update_action_; }
void TheoreticalOpeningPrice16Message::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

std::uint16_t TheoreticalOpeningPrice16Message::trade_date() const { return trade_date_; }
void TheoreticalOpeningPrice16Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::optional<Decimal> TheoreticalOpeningPrice16Message::md_corporate_offset_price_optional() const { return md_corporate_offset_price_optional_; }
void TheoreticalOpeningPrice16Message::set_md_corporate_offset_price_optional(std::optional<Decimal> value) { md_corporate_offset_price_optional_ = value; }

std::optional<std::int64_t> TheoreticalOpeningPrice16Message::md_entry_size_quantity_optional() const { return md_entry_size_quantity_optional_; }
void TheoreticalOpeningPrice16Message::set_md_entry_size_quantity_optional(std::optional<std::int64_t> value) { md_entry_size_quantity_optional_ = value; }

std::optional<std::chrono::nanoseconds> TheoreticalOpeningPrice16Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void TheoreticalOpeningPrice16Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> TheoreticalOpeningPrice16Message::rpt_seq() const { return rpt_seq_; }
void TheoreticalOpeningPrice16Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode TheoreticalOpeningPrice16Message::type() const { return message_type; }

std::string_view TheoreticalOpeningPrice16Message::name() const { return "Theoretical Opening Price 16 Message"; }

std::size_t TheoreticalOpeningPrice16Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TheoreticalOpeningPrice16Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    md_corporate_offset_price_optional_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    md_entry_size_quantity_optional_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t TheoreticalOpeningPrice16Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TheoreticalOpeningPrice16Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_i64_le(data + offset, md_corporate_offset_price_optional_ ? static_cast<std::int64_t>(md_corporate_offset_price_optional_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, md_entry_size_quantity_optional_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t TheoreticalOpeningPrice16Message::encoded_size() const {
    return wire_size;
}

void TheoreticalOpeningPrice16Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TheoreticalOpeningPrice16Message::clone() const {
    return std::make_unique<TheoreticalOpeningPrice16Message>(*this);
}

void TheoreticalOpeningPrice16Message::print(std::ostream& out) const {
    out << "TheoreticalOpeningPrice16Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", trade_date=";
    out << trade_date_;
    out << ", md_corporate_offset_price_optional=";
    print::optional(out, md_corporate_offset_price_optional_);
    out << ", md_entry_size_quantity_optional=";
    print::optional(out, md_entry_size_quantity_optional_);
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool TheoreticalOpeningPrice16Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TheoreticalOpeningPrice16Message*>(&other);
    return that != nullptr && *this == *that;
}

bool TheoreticalOpeningPrice16Message::operator==(const TheoreticalOpeningPrice16Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && md_update_action_ == other.md_update_action_
        && trade_date_ == other.trade_date_
        && md_corporate_offset_price_optional_ == other.md_corporate_offset_price_optional_
        && md_entry_size_quantity_optional_ == other.md_entry_size_quantity_optional_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool TheoreticalOpeningPrice16Message::operator!=(const TheoreticalOpeningPrice16Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
