#include "OpenInterest29Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

OpenInterest29Message::OpenInterest29Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 1>& offset_9_padding_1, std::uint16_t trade_date, std::int64_t md_entry_size_quantity, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), offset_9_padding_1_(offset_9_padding_1), trade_date_(trade_date), md_entry_size_quantity_(md_entry_size_quantity), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t OpenInterest29Message::security_id() const { return security_id_; }
void OpenInterest29Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& OpenInterest29Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& OpenInterest29Message::match_event_indicator() { return match_event_indicator_; }
void OpenInterest29Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 1>& OpenInterest29Message::offset_9_padding_1() const { return offset_9_padding_1_; }
std::array<std::byte, 1>& OpenInterest29Message::offset_9_padding_1() { return offset_9_padding_1_; }
void OpenInterest29Message::set_offset_9_padding_1(const std::array<std::byte, 1>& value) { offset_9_padding_1_ = value; }

std::uint16_t OpenInterest29Message::trade_date() const { return trade_date_; }
void OpenInterest29Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::int64_t OpenInterest29Message::md_entry_size_quantity() const { return md_entry_size_quantity_; }
void OpenInterest29Message::set_md_entry_size_quantity(std::int64_t value) { md_entry_size_quantity_ = value; }

std::optional<std::chrono::nanoseconds> OpenInterest29Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void OpenInterest29Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> OpenInterest29Message::rpt_seq() const { return rpt_seq_; }
void OpenInterest29Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode OpenInterest29Message::type() const { return message_type; }

std::string_view OpenInterest29Message::name() const { return "Open Interest 29 Message"; }

std::size_t OpenInterest29Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OpenInterest29Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, offset_9_padding_1_.data(), 1);
    offset += 1;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    md_entry_size_quantity_ = wire::read_i64_le(data + offset);
    offset += 8;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t OpenInterest29Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OpenInterest29Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_9_padding_1_.data(), 1);
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_entry_size_quantity_));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t OpenInterest29Message::encoded_size() const {
    return wire_size;
}

void OpenInterest29Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OpenInterest29Message::clone() const {
    return std::make_unique<OpenInterest29Message>(*this);
}

void OpenInterest29Message::print(std::ostream& out) const {
    out << "OpenInterest29Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", offset_9_padding_1=";
    print::hex(out, offset_9_padding_1_.data(), offset_9_padding_1_.size());
    out << ", trade_date=";
    out << trade_date_;
    out << ", md_entry_size_quantity=";
    out << md_entry_size_quantity_;
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool OpenInterest29Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OpenInterest29Message*>(&other);
    return that != nullptr && *this == *that;
}

bool OpenInterest29Message::operator==(const OpenInterest29Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && offset_9_padding_1_ == other.offset_9_padding_1_
        && trade_date_ == other.trade_date_
        && md_entry_size_quantity_ == other.md_entry_size_quantity_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool OpenInterest29Message::operator!=(const OpenInterest29Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
