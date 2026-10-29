#include "TrfFractionalTradeCorrectionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

TrfFractionalTradeCorrectionMessage::TrfFractionalTradeCorrectionMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t original_trade_id, std::uint32_t trade_id, std::int32_t price, std::uint64_t fractional_volume, TradeCond1 trade_cond_1, TradeCond2 trade_cond_2, TradeCond3 trade_cond_3, TradeCond4 trade_cond_4, std::uint32_t exec_day_time, std::uint32_t exec_day_time_ns)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), original_trade_id_(original_trade_id), trade_id_(trade_id), price_(price), fractional_volume_(fractional_volume), trade_cond_1_(trade_cond_1), trade_cond_2_(trade_cond_2), trade_cond_3_(trade_cond_3), trade_cond_4_(trade_cond_4), exec_day_time_(exec_day_time), exec_day_time_ns_(exec_day_time_ns) {}

std::uint32_t TrfFractionalTradeCorrectionMessage::source_time() const { return source_time_; }
void TrfFractionalTradeCorrectionMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t TrfFractionalTradeCorrectionMessage::source_time_ns() const { return source_time_ns_; }
void TrfFractionalTradeCorrectionMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t TrfFractionalTradeCorrectionMessage::symbol_index() const { return symbol_index_; }
void TrfFractionalTradeCorrectionMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t TrfFractionalTradeCorrectionMessage::symbol_seq_num() const { return symbol_seq_num_; }
void TrfFractionalTradeCorrectionMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t TrfFractionalTradeCorrectionMessage::original_trade_id() const { return original_trade_id_; }
void TrfFractionalTradeCorrectionMessage::set_original_trade_id(std::uint32_t value) { original_trade_id_ = value; }

std::uint32_t TrfFractionalTradeCorrectionMessage::trade_id() const { return trade_id_; }
void TrfFractionalTradeCorrectionMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t TrfFractionalTradeCorrectionMessage::price() const { return price_; }
void TrfFractionalTradeCorrectionMessage::set_price(std::int32_t value) { price_ = value; }

std::uint64_t TrfFractionalTradeCorrectionMessage::fractional_volume() const { return fractional_volume_; }
void TrfFractionalTradeCorrectionMessage::set_fractional_volume(std::uint64_t value) { fractional_volume_ = value; }

TradeCond1 TrfFractionalTradeCorrectionMessage::trade_cond_1() const { return trade_cond_1_; }
void TrfFractionalTradeCorrectionMessage::set_trade_cond_1(TradeCond1 value) { trade_cond_1_ = value; }

TradeCond2 TrfFractionalTradeCorrectionMessage::trade_cond_2() const { return trade_cond_2_; }
void TrfFractionalTradeCorrectionMessage::set_trade_cond_2(TradeCond2 value) { trade_cond_2_ = value; }

TradeCond3 TrfFractionalTradeCorrectionMessage::trade_cond_3() const { return trade_cond_3_; }
void TrfFractionalTradeCorrectionMessage::set_trade_cond_3(TradeCond3 value) { trade_cond_3_ = value; }

TradeCond4 TrfFractionalTradeCorrectionMessage::trade_cond_4() const { return trade_cond_4_; }
void TrfFractionalTradeCorrectionMessage::set_trade_cond_4(TradeCond4 value) { trade_cond_4_ = value; }

std::uint32_t TrfFractionalTradeCorrectionMessage::exec_day_time() const { return exec_day_time_; }
void TrfFractionalTradeCorrectionMessage::set_exec_day_time(std::uint32_t value) { exec_day_time_ = value; }

std::uint32_t TrfFractionalTradeCorrectionMessage::exec_day_time_ns() const { return exec_day_time_ns_; }
void TrfFractionalTradeCorrectionMessage::set_exec_day_time_ns(std::uint32_t value) { exec_day_time_ns_ = value; }

MessageCode TrfFractionalTradeCorrectionMessage::type() const { return message_type; }

std::string_view TrfFractionalTradeCorrectionMessage::name() const { return "Trf Fractional Trade Correction Message"; }

std::size_t TrfFractionalTradeCorrectionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TrfFractionalTradeCorrectionMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    original_trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    trade_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    fractional_volume_ = wire::read_u64_le(data + offset);
    offset += 8;

    trade_cond_1_ = static_cast<TradeCond1>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_2_ = static_cast<TradeCond2>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_3_ = static_cast<TradeCond3>(wire::read_char(data + offset));
    offset += 1;

    trade_cond_4_ = static_cast<TradeCond4>(wire::read_char(data + offset));
    offset += 1;

    exec_day_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    exec_day_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TrfFractionalTradeCorrectionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TrfFractionalTradeCorrectionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(original_trade_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(trade_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(fractional_volume_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trade_cond_1_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_2_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_3_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(trade_cond_4_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(exec_day_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(exec_day_time_ns_));
    offset += 4;

    return offset;
}

std::size_t TrfFractionalTradeCorrectionMessage::encoded_size() const {
    return wire_size;
}

void TrfFractionalTradeCorrectionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TrfFractionalTradeCorrectionMessage::clone() const {
    return std::make_unique<TrfFractionalTradeCorrectionMessage>(*this);
}

void TrfFractionalTradeCorrectionMessage::print(std::ostream& out) const {
    out << "TrfFractionalTradeCorrectionMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", original_trade_id=";
    out << original_trade_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", fractional_volume=";
    out << fractional_volume_;
    out << ", trade_cond_1=";
    out << trade_cond_1_;
    out << ", trade_cond_2=";
    out << trade_cond_2_;
    out << ", trade_cond_3=";
    out << trade_cond_3_;
    out << ", trade_cond_4=";
    out << trade_cond_4_;
    out << ", exec_day_time=";
    out << exec_day_time_;
    out << ", exec_day_time_ns=";
    out << exec_day_time_ns_;
    out << '}';
}

bool TrfFractionalTradeCorrectionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TrfFractionalTradeCorrectionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TrfFractionalTradeCorrectionMessage::operator==(const TrfFractionalTradeCorrectionMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && original_trade_id_ == other.original_trade_id_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && fractional_volume_ == other.fractional_volume_
        && trade_cond_1_ == other.trade_cond_1_
        && trade_cond_2_ == other.trade_cond_2_
        && trade_cond_3_ == other.trade_cond_3_
        && trade_cond_4_ == other.trade_cond_4_
        && exec_day_time_ == other.exec_day_time_
        && exec_day_time_ns_ == other.exec_day_time_ns_;
}

bool TrfFractionalTradeCorrectionMessage::operator!=(const TrfFractionalTradeCorrectionMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
