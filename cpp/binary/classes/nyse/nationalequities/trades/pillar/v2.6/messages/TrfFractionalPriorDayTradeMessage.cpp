#include "TrfFractionalPriorDayTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

TrfFractionalPriorDayTradeMessage::TrfFractionalPriorDayTradeMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint64_t fractional_volume, TradeCond1 trade_cond_1, TradeCond2 trade_cond_2, TradeCond3 trade_cond_3, TradeCond4 trade_cond_4, std::uint32_t prior_day_time, std::uint32_t prior_day_time_ns)
  : source_time_(source_time), source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), trade_id_(trade_id), price_(price), fractional_volume_(fractional_volume), trade_cond_1_(trade_cond_1), trade_cond_2_(trade_cond_2), trade_cond_3_(trade_cond_3), trade_cond_4_(trade_cond_4), prior_day_time_(prior_day_time), prior_day_time_ns_(prior_day_time_ns) {}

std::uint32_t TrfFractionalPriorDayTradeMessage::source_time() const { return source_time_; }
void TrfFractionalPriorDayTradeMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t TrfFractionalPriorDayTradeMessage::source_time_ns() const { return source_time_ns_; }
void TrfFractionalPriorDayTradeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t TrfFractionalPriorDayTradeMessage::symbol_index() const { return symbol_index_; }
void TrfFractionalPriorDayTradeMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t TrfFractionalPriorDayTradeMessage::symbol_seq_num() const { return symbol_seq_num_; }
void TrfFractionalPriorDayTradeMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t TrfFractionalPriorDayTradeMessage::trade_id() const { return trade_id_; }
void TrfFractionalPriorDayTradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t TrfFractionalPriorDayTradeMessage::price() const { return price_; }
void TrfFractionalPriorDayTradeMessage::set_price(std::int32_t value) { price_ = value; }

std::uint64_t TrfFractionalPriorDayTradeMessage::fractional_volume() const { return fractional_volume_; }
void TrfFractionalPriorDayTradeMessage::set_fractional_volume(std::uint64_t value) { fractional_volume_ = value; }

TradeCond1 TrfFractionalPriorDayTradeMessage::trade_cond_1() const { return trade_cond_1_; }
void TrfFractionalPriorDayTradeMessage::set_trade_cond_1(TradeCond1 value) { trade_cond_1_ = value; }

TradeCond2 TrfFractionalPriorDayTradeMessage::trade_cond_2() const { return trade_cond_2_; }
void TrfFractionalPriorDayTradeMessage::set_trade_cond_2(TradeCond2 value) { trade_cond_2_ = value; }

TradeCond3 TrfFractionalPriorDayTradeMessage::trade_cond_3() const { return trade_cond_3_; }
void TrfFractionalPriorDayTradeMessage::set_trade_cond_3(TradeCond3 value) { trade_cond_3_ = value; }

TradeCond4 TrfFractionalPriorDayTradeMessage::trade_cond_4() const { return trade_cond_4_; }
void TrfFractionalPriorDayTradeMessage::set_trade_cond_4(TradeCond4 value) { trade_cond_4_ = value; }

std::uint32_t TrfFractionalPriorDayTradeMessage::prior_day_time() const { return prior_day_time_; }
void TrfFractionalPriorDayTradeMessage::set_prior_day_time(std::uint32_t value) { prior_day_time_ = value; }

std::uint32_t TrfFractionalPriorDayTradeMessage::prior_day_time_ns() const { return prior_day_time_ns_; }
void TrfFractionalPriorDayTradeMessage::set_prior_day_time_ns(std::uint32_t value) { prior_day_time_ns_ = value; }

MessageCode TrfFractionalPriorDayTradeMessage::type() const { return message_type; }

std::string_view TrfFractionalPriorDayTradeMessage::name() const { return "Trf Fractional Prior Day Trade Message"; }

std::size_t TrfFractionalPriorDayTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TrfFractionalPriorDayTradeMessage", wire_size, length);

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

    prior_day_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    prior_day_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TrfFractionalPriorDayTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TrfFractionalPriorDayTradeMessage", wire_size, capacity);

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

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(prior_day_time_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(prior_day_time_ns_));
    offset += 4;

    return offset;
}

std::size_t TrfFractionalPriorDayTradeMessage::encoded_size() const {
    return wire_size;
}

void TrfFractionalPriorDayTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TrfFractionalPriorDayTradeMessage::clone() const {
    return std::make_unique<TrfFractionalPriorDayTradeMessage>(*this);
}

void TrfFractionalPriorDayTradeMessage::print(std::ostream& out) const {
    out << "TrfFractionalPriorDayTradeMessage{";
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
    out << ", prior_day_time=";
    out << prior_day_time_;
    out << ", prior_day_time_ns=";
    out << prior_day_time_ns_;
    out << '}';
}

bool TrfFractionalPriorDayTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TrfFractionalPriorDayTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TrfFractionalPriorDayTradeMessage::operator==(const TrfFractionalPriorDayTradeMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && fractional_volume_ == other.fractional_volume_
        && trade_cond_1_ == other.trade_cond_1_
        && trade_cond_2_ == other.trade_cond_2_
        && trade_cond_3_ == other.trade_cond_3_
        && trade_cond_4_ == other.trade_cond_4_
        && prior_day_time_ == other.prior_day_time_
        && prior_day_time_ns_ == other.prior_day_time_ns_;
}

bool TrfFractionalPriorDayTradeMessage::operator!=(const TrfFractionalPriorDayTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
