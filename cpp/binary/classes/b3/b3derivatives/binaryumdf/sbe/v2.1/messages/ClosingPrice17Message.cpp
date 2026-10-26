#include "ClosingPrice17Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

ClosingPrice17Message::ClosingPrice17Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, OpenCloseSettlFlag open_close_settl_flag, const std::array<std::byte, 2>& offset_10_padding_2, Decimal md_corporate_price, std::optional<std::uint16_t> last_trade_date, std::uint16_t trade_date, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), open_close_settl_flag_(open_close_settl_flag), offset_10_padding_2_(offset_10_padding_2), md_corporate_price_(md_corporate_price), last_trade_date_(last_trade_date), trade_date_(trade_date), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq) {}

std::uint64_t ClosingPrice17Message::security_id() const { return security_id_; }
void ClosingPrice17Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& ClosingPrice17Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ClosingPrice17Message::match_event_indicator() { return match_event_indicator_; }
void ClosingPrice17Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

OpenCloseSettlFlag ClosingPrice17Message::open_close_settl_flag() const { return open_close_settl_flag_; }
void ClosingPrice17Message::set_open_close_settl_flag(OpenCloseSettlFlag value) { open_close_settl_flag_ = value; }

const std::array<std::byte, 2>& ClosingPrice17Message::offset_10_padding_2() const { return offset_10_padding_2_; }
std::array<std::byte, 2>& ClosingPrice17Message::offset_10_padding_2() { return offset_10_padding_2_; }
void ClosingPrice17Message::set_offset_10_padding_2(const std::array<std::byte, 2>& value) { offset_10_padding_2_ = value; }

Decimal ClosingPrice17Message::md_corporate_price() const { return md_corporate_price_; }
void ClosingPrice17Message::set_md_corporate_price(Decimal value) { md_corporate_price_ = value; }

std::optional<std::uint16_t> ClosingPrice17Message::last_trade_date() const { return last_trade_date_; }
void ClosingPrice17Message::set_last_trade_date(std::optional<std::uint16_t> value) { last_trade_date_ = value; }

std::uint16_t ClosingPrice17Message::trade_date() const { return trade_date_; }
void ClosingPrice17Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::optional<std::chrono::nanoseconds> ClosingPrice17Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void ClosingPrice17Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> ClosingPrice17Message::rpt_seq() const { return rpt_seq_; }
void ClosingPrice17Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

MessageCode ClosingPrice17Message::type() const { return message_type; }

std::string_view ClosingPrice17Message::name() const { return "Closing Price 17 Message"; }

std::size_t ClosingPrice17Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ClosingPrice17Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    open_close_settl_flag_ = static_cast<OpenCloseSettlFlag>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_10_padding_2_.data(), 2);
    offset += 2;

    md_corporate_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -8);
    offset += 8;

    last_trade_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    return offset;
}

std::size_t ClosingPrice17Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClosingPrice17Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(open_close_settl_flag_));
    offset += 1;

    wire::write_bytes(data + offset, offset_10_padding_2_.data(), 2);
    offset += 2;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_corporate_price_.mantissa()));
    offset += 8;

    wire::write_u16_le(data + offset, last_trade_date_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    return offset;
}

std::size_t ClosingPrice17Message::encoded_size() const {
    return wire_size;
}

void ClosingPrice17Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ClosingPrice17Message::clone() const {
    return std::make_unique<ClosingPrice17Message>(*this);
}

void ClosingPrice17Message::print(std::ostream& out) const {
    out << "ClosingPrice17Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", open_close_settl_flag=";
    out << open_close_settl_flag_;
    out << ", offset_10_padding_2=";
    print::hex(out, offset_10_padding_2_.data(), offset_10_padding_2_.size());
    out << ", md_corporate_price=";
    out << md_corporate_price_;
    out << ", last_trade_date=";
    print::optional(out, last_trade_date_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << '}';
}

bool ClosingPrice17Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ClosingPrice17Message*>(&other);
    return that != nullptr && *this == *that;
}

bool ClosingPrice17Message::operator==(const ClosingPrice17Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && open_close_settl_flag_ == other.open_close_settl_flag_
        && offset_10_padding_2_ == other.offset_10_padding_2_
        && md_corporate_price_ == other.md_corporate_price_
        && last_trade_date_ == other.last_trade_date_
        && trade_date_ == other.trade_date_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_;
}

bool ClosingPrice17Message::operator!=(const ClosingPrice17Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
