#include "OpeningPrice15Message.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

OpeningPrice15Message::OpeningPrice15Message(std::uint64_t security_id, const MatchEventIndicator& match_event_indicator, MdUpdateAction md_update_action, OpenCloseSettlFlag open_close_settl_flag, const std::array<std::byte, 1>& offset_11_padding_1, Decimal md_future_price, std::optional<Decimal> net_chg_prev_day, std::uint16_t trade_date, std::optional<std::chrono::nanoseconds> md_entry_timestamp, std::optional<std::uint32_t> rpt_seq, const std::array<std::byte, 2>& padding_2)
  : security_id_(security_id), match_event_indicator_(match_event_indicator), md_update_action_(md_update_action), open_close_settl_flag_(open_close_settl_flag), offset_11_padding_1_(offset_11_padding_1), md_future_price_(md_future_price), net_chg_prev_day_(net_chg_prev_day), trade_date_(trade_date), md_entry_timestamp_(md_entry_timestamp), rpt_seq_(rpt_seq), padding_2_(padding_2) {}

std::uint64_t OpeningPrice15Message::security_id() const { return security_id_; }
void OpeningPrice15Message::set_security_id(std::uint64_t value) { security_id_ = value; }

const MatchEventIndicator& OpeningPrice15Message::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& OpeningPrice15Message::match_event_indicator() { return match_event_indicator_; }
void OpeningPrice15Message::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

MdUpdateAction OpeningPrice15Message::md_update_action() const { return md_update_action_; }
void OpeningPrice15Message::set_md_update_action(MdUpdateAction value) { md_update_action_ = value; }

OpenCloseSettlFlag OpeningPrice15Message::open_close_settl_flag() const { return open_close_settl_flag_; }
void OpeningPrice15Message::set_open_close_settl_flag(OpenCloseSettlFlag value) { open_close_settl_flag_ = value; }

const std::array<std::byte, 1>& OpeningPrice15Message::offset_11_padding_1() const { return offset_11_padding_1_; }
std::array<std::byte, 1>& OpeningPrice15Message::offset_11_padding_1() { return offset_11_padding_1_; }
void OpeningPrice15Message::set_offset_11_padding_1(const std::array<std::byte, 1>& value) { offset_11_padding_1_ = value; }

Decimal OpeningPrice15Message::md_future_price() const { return md_future_price_; }
void OpeningPrice15Message::set_md_future_price(Decimal value) { md_future_price_ = value; }

std::optional<Decimal> OpeningPrice15Message::net_chg_prev_day() const { return net_chg_prev_day_; }
void OpeningPrice15Message::set_net_chg_prev_day(std::optional<Decimal> value) { net_chg_prev_day_ = value; }

std::uint16_t OpeningPrice15Message::trade_date() const { return trade_date_; }
void OpeningPrice15Message::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::optional<std::chrono::nanoseconds> OpeningPrice15Message::md_entry_timestamp() const { return md_entry_timestamp_; }
void OpeningPrice15Message::set_md_entry_timestamp(std::optional<std::chrono::nanoseconds> value) { md_entry_timestamp_ = value; }

std::optional<std::uint32_t> OpeningPrice15Message::rpt_seq() const { return rpt_seq_; }
void OpeningPrice15Message::set_rpt_seq(std::optional<std::uint32_t> value) { rpt_seq_ = value; }

const std::array<std::byte, 2>& OpeningPrice15Message::padding_2() const { return padding_2_; }
std::array<std::byte, 2>& OpeningPrice15Message::padding_2() { return padding_2_; }
void OpeningPrice15Message::set_padding_2(const std::array<std::byte, 2>& value) { padding_2_ = value; }

MessageCode OpeningPrice15Message::type() const { return message_type; }

std::string_view OpeningPrice15Message::name() const { return "Opening Price 15 Message"; }

std::size_t OpeningPrice15Message::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OpeningPrice15Message", wire_size, length);

    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    md_update_action_ = static_cast<MdUpdateAction>(wire::read_u8(data + offset));
    offset += 1;

    open_close_settl_flag_ = static_cast<OpenCloseSettlFlag>(wire::read_u8(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    md_future_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    net_chg_prev_day_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    trade_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    md_entry_timestamp_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    rpt_seq_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::read_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t OpeningPrice15Message::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OpeningPrice15Message", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(md_update_action_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(open_close_settl_flag_));
    offset += 1;

    wire::write_bytes(data + offset, offset_11_padding_1_.data(), 1);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(md_future_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, net_chg_prev_day_ ? static_cast<std::int64_t>(net_chg_prev_day_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u64_le(data + offset, md_entry_timestamp_ ? static_cast<std::uint64_t>(md_entry_timestamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, rpt_seq_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_bytes(data + offset, padding_2_.data(), 2);
    offset += 2;

    return offset;
}

std::size_t OpeningPrice15Message::encoded_size() const {
    return wire_size;
}

void OpeningPrice15Message::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OpeningPrice15Message::clone() const {
    return std::make_unique<OpeningPrice15Message>(*this);
}

void OpeningPrice15Message::print(std::ostream& out) const {
    out << "OpeningPrice15Message{";
    out << "security_id=";
    out << security_id_;
    out << ", match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", md_update_action=";
    out << md_update_action_;
    out << ", open_close_settl_flag=";
    out << open_close_settl_flag_;
    out << ", offset_11_padding_1=";
    print::hex(out, offset_11_padding_1_.data(), offset_11_padding_1_.size());
    out << ", md_future_price=";
    out << md_future_price_;
    out << ", net_chg_prev_day=";
    print::optional(out, net_chg_prev_day_);
    out << ", trade_date=";
    out << trade_date_;
    out << ", md_entry_timestamp=";
    print::optional_duration(out, md_entry_timestamp_);
    out << ", rpt_seq=";
    print::optional(out, rpt_seq_);
    out << ", padding_2=";
    print::hex(out, padding_2_.data(), padding_2_.size());
    out << '}';
}

bool OpeningPrice15Message::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OpeningPrice15Message*>(&other);
    return that != nullptr && *this == *that;
}

bool OpeningPrice15Message::operator==(const OpeningPrice15Message& other) const {
    return security_id_ == other.security_id_
        && match_event_indicator_ == other.match_event_indicator_
        && md_update_action_ == other.md_update_action_
        && open_close_settl_flag_ == other.open_close_settl_flag_
        && offset_11_padding_1_ == other.offset_11_padding_1_
        && md_future_price_ == other.md_future_price_
        && net_chg_prev_day_ == other.net_chg_prev_day_
        && trade_date_ == other.trade_date_
        && md_entry_timestamp_ == other.md_entry_timestamp_
        && rpt_seq_ == other.rpt_seq_
        && padding_2_ == other.padding_2_;
}

bool OpeningPrice15Message::operator!=(const OpeningPrice15Message& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
