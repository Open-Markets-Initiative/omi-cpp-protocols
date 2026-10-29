#include "TradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

TradeMessage::TradeMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, TradeCond1 trade_cond_1, TradeCond2 trade_cond_2, TradeCond3 trade_cond_3, TradeCond4 trade_cond_4)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), trade_id_(trade_id), price_(price), volume_(volume), trade_cond_1_(trade_cond_1), trade_cond_2_(trade_cond_2), trade_cond_3_(trade_cond_3), trade_cond_4_(trade_cond_4) {}

std::uint32_t TradeMessage::source_time() const { return source_time_; }
void TradeMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t TradeMessage::source_time_ns() const { return source_time_ns_; }
void TradeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t TradeMessage::symbol_index() const { return symbol_index_; }
void TradeMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t TradeMessage::symbol_seq_num() const { return symbol_seq_num_; }
void TradeMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t TradeMessage::trade_id() const { return trade_id_; }
void TradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t TradeMessage::price() const { return price_; }
void TradeMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t TradeMessage::volume() const { return volume_; }
void TradeMessage::set_volume(std::uint32_t value) { volume_ = value; }

TradeCond1 TradeMessage::trade_cond_1() const { return trade_cond_1_; }
void TradeMessage::set_trade_cond_1(TradeCond1 value) { trade_cond_1_ = value; }

TradeCond2 TradeMessage::trade_cond_2() const { return trade_cond_2_; }
void TradeMessage::set_trade_cond_2(TradeCond2 value) { trade_cond_2_ = value; }

TradeCond3 TradeMessage::trade_cond_3() const { return trade_cond_3_; }
void TradeMessage::set_trade_cond_3(TradeCond3 value) { trade_cond_3_ = value; }

TradeCond4 TradeMessage::trade_cond_4() const { return trade_cond_4_; }
void TradeMessage::set_trade_cond_4(TradeCond4 value) { trade_cond_4_ = value; }

MessageCode TradeMessage::type() const { return message_type; }

std::string_view TradeMessage::name() const { return "Trade Message"; }

std::size_t TradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
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

std::size_t TradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
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

std::size_t TradeMessage::encoded_size() const {
    return wire_size;
}

void TradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeMessage::clone() const {
    return std::make_unique<TradeMessage>(*this);
}

void TradeMessage::print(std::ostream& out) const {
    out << "TradeMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
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

bool TradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeMessage::operator==(const TradeMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && trade_cond_1_ == other.trade_cond_1_
        && trade_cond_2_ == other.trade_cond_2_
        && trade_cond_3_ == other.trade_cond_3_
        && trade_cond_4_ == other.trade_cond_4_;
}

bool TradeMessage::operator!=(const TradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
