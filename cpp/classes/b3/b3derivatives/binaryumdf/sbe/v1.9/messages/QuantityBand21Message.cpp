#include "QuantityBand21Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

QuantityBand21Message::QuantityBand21Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, const std::array<std::byte, 3>& offset_9_padding_3, std::optional<std::int64_t> avg_daily_traded_qty, std::optional<std::int64_t> max_trade_vol, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), offset_9_padding_3_(offset_9_padding_3), avg_daily_traded_qty_(avg_daily_traded_qty), max_trade_vol_(max_trade_vol), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t QuantityBand21Message::security_id() const { return security_id_; }
void QuantityBand21Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& QuantityBand21Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& QuantityBand21Message::match_event_indicator() { return match_event_indicator_; }
void QuantityBand21Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

const std::array<std::byte, 3>& QuantityBand21Message::offset_9_padding_3() const { return offset_9_padding_3_; }
std::array<std::byte, 3>& QuantityBand21Message::offset_9_padding_3() { return offset_9_padding_3_; }
void QuantityBand21Message::set_offset_9_padding_3(const std::array<std::byte, 3>& value) { offset_9_padding_3_ = value; }

std::optional<std::int64_t> QuantityBand21Message::avg_daily_traded_qty() const { return avg_daily_traded_qty_; }
void QuantityBand21Message::set_avg_daily_traded_qty(std::optional<std::int64_t> value) { avg_daily_traded_qty_ = value; }

std::optional<std::int64_t> QuantityBand21Message::max_trade_vol() const { return max_trade_vol_; }
void QuantityBand21Message::set_max_trade_vol(std::optional<std::int64_t> value) { max_trade_vol_ = value; }

std::optional<std::chrono::nanoseconds> QuantityBand21Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void QuantityBand21Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> QuantityBand21Message::rpt_seq() const { return rpt_seq_; }
void QuantityBand21Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode QuantityBand21Message::type() const { return message_type; }

std::string_view QuantityBand21Message::name() const { return "Quantity Band 21 Message"; }

std::size_t QuantityBand21Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuantityBand21Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::read_bytes(data + offset, offset_9_padding_3_.data(), 3);
    offset += 3;

    avg_daily_traded_qty_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    max_trade_vol_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t QuantityBand21Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuantityBand21Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_bytes(data + offset, offset_9_padding_3_.data(), 3);
    offset += 3;

    wire::write_i64_le(data + offset, avg_daily_traded_qty_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_i64_le(data + offset, max_trade_vol_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t QuantityBand21Message::encoded_size() const {
    return wire_size;
}

void QuantityBand21Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuantityBand21Message::clone() const {
    return std::make_unique<QuantityBand21Message>(*this);
}

void QuantityBand21Message::print(std::ostream& out) const {
    out << "QuantityBand21Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", offset_9_padding_3=";
    print::hex(out, offset_9_padding_3_.data(), offset_9_padding_3_.size());
    out << ", avg_daily_traded_qty=";
    print::optional(out, avg_daily_traded_qty_);
    out << ", max_trade_vol=";
    print::optional(out, max_trade_vol_);
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool QuantityBand21Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuantityBand21Message*>(&other);
    return that != nullptr && *this == *that;
}

bool QuantityBand21Message::operator==(const QuantityBand21Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && offset_9_padding_3_ == other.offset_9_padding_3_
        && avg_daily_traded_qty_ == other.avg_daily_traded_qty_
        && max_trade_vol_ == other.max_trade_vol_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool QuantityBand21Message::operator!=(const QuantityBand21Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
