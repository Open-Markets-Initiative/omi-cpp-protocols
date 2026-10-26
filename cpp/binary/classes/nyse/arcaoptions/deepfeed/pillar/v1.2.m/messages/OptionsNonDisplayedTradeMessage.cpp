#include "OptionsNonDisplayedTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsNonDisplayedTradeMessage::OptionsNonDisplayedTradeMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, PrintableFlag printable_flag, NonDisplayedTradeTradeCond1 non_displayed_trade_trade_cond_1, const std::array<std::byte, 3>& reserved_3, PriceType price_type)
  : source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), trade_id_(trade_id), price_(price), volume_(volume), printable_flag_(printable_flag), non_displayed_trade_trade_cond_1_(non_displayed_trade_trade_cond_1), reserved_3_(reserved_3), price_type_(price_type) {}

std::uint32_t OptionsNonDisplayedTradeMessage::source_time_ns() const { return source_time_ns_; }
void OptionsNonDisplayedTradeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsNonDisplayedTradeMessage::series_index() const { return series_index_; }
void OptionsNonDisplayedTradeMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsNonDisplayedTradeMessage::series_seq_num() const { return series_seq_num_; }
void OptionsNonDisplayedTradeMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint32_t OptionsNonDisplayedTradeMessage::trade_id() const { return trade_id_; }
void OptionsNonDisplayedTradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t OptionsNonDisplayedTradeMessage::price() const { return price_; }
void OptionsNonDisplayedTradeMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OptionsNonDisplayedTradeMessage::volume() const { return volume_; }
void OptionsNonDisplayedTradeMessage::set_volume(std::uint32_t value) { volume_ = value; }

PrintableFlag OptionsNonDisplayedTradeMessage::printable_flag() const { return printable_flag_; }
void OptionsNonDisplayedTradeMessage::set_printable_flag(PrintableFlag value) { printable_flag_ = value; }

NonDisplayedTradeTradeCond1 OptionsNonDisplayedTradeMessage::non_displayed_trade_trade_cond_1() const { return non_displayed_trade_trade_cond_1_; }
void OptionsNonDisplayedTradeMessage::set_non_displayed_trade_trade_cond_1(NonDisplayedTradeTradeCond1 value) { non_displayed_trade_trade_cond_1_ = value; }

const std::array<std::byte, 3>& OptionsNonDisplayedTradeMessage::reserved_3() const { return reserved_3_; }
std::array<std::byte, 3>& OptionsNonDisplayedTradeMessage::reserved_3() { return reserved_3_; }
void OptionsNonDisplayedTradeMessage::set_reserved_3(const std::array<std::byte, 3>& value) { reserved_3_ = value; }

PriceType OptionsNonDisplayedTradeMessage::price_type() const { return price_type_; }
void OptionsNonDisplayedTradeMessage::set_price_type(PriceType value) { price_type_ = value; }

MessageCode OptionsNonDisplayedTradeMessage::type() const { return message_type; }

std::string_view OptionsNonDisplayedTradeMessage::name() const { return "Options Non Displayed Trade Message"; }

std::size_t OptionsNonDisplayedTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsNonDisplayedTradeMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    printable_flag_ = static_cast<PrintableFlag>(wire::read_u8(data + offset));
    offset += 1;

    non_displayed_trade_trade_cond_1_ = static_cast<NonDisplayedTradeTradeCond1>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    price_type_ = static_cast<PriceType>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsNonDisplayedTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsNonDisplayedTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(printable_flag_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(non_displayed_trade_trade_cond_1_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_3_.data(), 3);
    offset += 3;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_type_));
    offset += 1;

    return offset;
}

std::size_t OptionsNonDisplayedTradeMessage::encoded_size() const {
    return wire_size;
}

void OptionsNonDisplayedTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsNonDisplayedTradeMessage::clone() const {
    return std::make_unique<OptionsNonDisplayedTradeMessage>(*this);
}

void OptionsNonDisplayedTradeMessage::print(std::ostream& out) const {
    out << "OptionsNonDisplayedTradeMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", printable_flag=";
    out << printable_flag_;
    out << ", non_displayed_trade_trade_cond_1=";
    out << non_displayed_trade_trade_cond_1_;
    out << ", reserved_3=";
    print::hex(out, reserved_3_.data(), reserved_3_.size());
    out << ", price_type=";
    out << price_type_;
    out << '}';
}

bool OptionsNonDisplayedTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsNonDisplayedTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsNonDisplayedTradeMessage::operator==(const OptionsNonDisplayedTradeMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && printable_flag_ == other.printable_flag_
        && non_displayed_trade_trade_cond_1_ == other.non_displayed_trade_trade_cond_1_
        && reserved_3_ == other.reserved_3_
        && price_type_ == other.price_type_;
}

bool OptionsNonDisplayedTradeMessage::operator!=(const OptionsNonDisplayedTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
