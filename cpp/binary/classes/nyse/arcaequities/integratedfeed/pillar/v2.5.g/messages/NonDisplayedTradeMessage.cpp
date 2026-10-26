#include "NonDisplayedTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

NonDisplayedTradeMessage::NonDisplayedTradeMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, PrintableFlag printable_flag, TradeCond1 trade_cond_1, TradeCond2 trade_cond_2, TradeCond3 trade_cond_3, TradeCond4 trade_cond_4)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), trade_id_(trade_id), price_(price), volume_(volume), printable_flag_(printable_flag), trade_cond_1_(trade_cond_1), trade_cond_2_(trade_cond_2), trade_cond_3_(trade_cond_3), trade_cond_4_(trade_cond_4) {}

std::chrono::nanoseconds NonDisplayedTradeMessage::source_time_ns() const { return source_time_ns_; }
void NonDisplayedTradeMessage::set_source_time_ns(std::chrono::nanoseconds value) { source_time_ns_ = value; }

std::uint32_t NonDisplayedTradeMessage::symbol_index() const { return symbol_index_; }
void NonDisplayedTradeMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t NonDisplayedTradeMessage::symbol_seq_num() const { return symbol_seq_num_; }
void NonDisplayedTradeMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t NonDisplayedTradeMessage::trade_id() const { return trade_id_; }
void NonDisplayedTradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t NonDisplayedTradeMessage::price() const { return price_; }
void NonDisplayedTradeMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t NonDisplayedTradeMessage::volume() const { return volume_; }
void NonDisplayedTradeMessage::set_volume(std::uint32_t value) { volume_ = value; }

PrintableFlag NonDisplayedTradeMessage::printable_flag() const { return printable_flag_; }
void NonDisplayedTradeMessage::set_printable_flag(PrintableFlag value) { printable_flag_ = value; }

TradeCond1 NonDisplayedTradeMessage::trade_cond_1() const { return trade_cond_1_; }
void NonDisplayedTradeMessage::set_trade_cond_1(TradeCond1 value) { trade_cond_1_ = value; }

TradeCond2 NonDisplayedTradeMessage::trade_cond_2() const { return trade_cond_2_; }
void NonDisplayedTradeMessage::set_trade_cond_2(TradeCond2 value) { trade_cond_2_ = value; }

TradeCond3 NonDisplayedTradeMessage::trade_cond_3() const { return trade_cond_3_; }
void NonDisplayedTradeMessage::set_trade_cond_3(TradeCond3 value) { trade_cond_3_ = value; }

TradeCond4 NonDisplayedTradeMessage::trade_cond_4() const { return trade_cond_4_; }
void NonDisplayedTradeMessage::set_trade_cond_4(TradeCond4 value) { trade_cond_4_ = value; }

MessageCode NonDisplayedTradeMessage::type() const { return message_type; }

std::string_view NonDisplayedTradeMessage::name() const { return "Non Displayed Trade Message"; }

std::size_t NonDisplayedTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NonDisplayedTradeMessage", wire_size, length);

    source_time_ns_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    printable_flag_ = static_cast<PrintableFlag>(wire::read_u8(data + offset));
    offset += 1;

    trade_cond_1_ = static_cast<TradeCond1>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_2_ = static_cast<TradeCond2>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_3_ = static_cast<TradeCond3>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_4_ = static_cast<TradeCond4>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t NonDisplayedTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NonDisplayedTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(printable_flag_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_1_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_2_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_3_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_4_));
    offset += 1;

    return offset;
}

std::size_t NonDisplayedTradeMessage::encoded_size() const {
    return wire_size;
}

void NonDisplayedTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NonDisplayedTradeMessage::clone() const {
    return std::make_unique<NonDisplayedTradeMessage>(*this);
}

void NonDisplayedTradeMessage::print(std::ostream& out) const {
    out << "NonDisplayedTradeMessage{";
    out << "source_time_ns=";
    out << source_time_ns_.count();
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", printable_flag=";
    out << printable_flag_;
    out << ", trade_cond_1=";
    out << trade_cond_1_;
    out << ", trade_cond_2=";
    out << trade_cond_2_;
    out << ", trade_cond_3=";
    out << trade_cond_3_;
    out << ", trade_cond_4=";
    out << trade_cond_4_;
    out << '}';
}

bool NonDisplayedTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NonDisplayedTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NonDisplayedTradeMessage::operator==(const NonDisplayedTradeMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && printable_flag_ == other.printable_flag_
        && trade_cond_1_ == other.trade_cond_1_
        && trade_cond_2_ == other.trade_cond_2_
        && trade_cond_3_ == other.trade_cond_3_
        && trade_cond_4_ == other.trade_cond_4_;
}

bool NonDisplayedTradeMessage::operator!=(const NonDisplayedTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g
