#include "OptionsTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

OptionsTradeMessage::OptionsTradeMessage(std::uint32_t source_time, std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t trade_id, std::int32_t price, std::uint32_t volume, const TradeCondition& trade_condition)
  : source_time_(source_time), source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), trade_id_(trade_id), price_(price), volume_(volume), trade_condition_(trade_condition) {}

std::uint32_t OptionsTradeMessage::source_time() const { return source_time_; }
void OptionsTradeMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

std::uint32_t OptionsTradeMessage::source_time_ns() const { return source_time_ns_; }
void OptionsTradeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsTradeMessage::series_index() const { return series_index_; }
void OptionsTradeMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsTradeMessage::series_seq_num() const { return series_seq_num_; }
void OptionsTradeMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint32_t OptionsTradeMessage::trade_id() const { return trade_id_; }
void OptionsTradeMessage::set_trade_id(std::uint32_t value) { trade_id_ = value; }

std::int32_t OptionsTradeMessage::price() const { return price_; }
void OptionsTradeMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OptionsTradeMessage::volume() const { return volume_; }
void OptionsTradeMessage::set_volume(std::uint32_t value) { volume_ = value; }

const TradeCondition& OptionsTradeMessage::trade_condition() const { return trade_condition_; }
TradeCondition& OptionsTradeMessage::trade_condition() { return trade_condition_; }
void OptionsTradeMessage::set_trade_condition(const TradeCondition& value) { trade_condition_ = value; }

MessageCode OptionsTradeMessage::type() const { return message_type; }

std::string_view OptionsTradeMessage::name() const { return "Options Trade Message"; }

std::size_t OptionsTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsTradeMessage", wire_size, length);

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

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

    offset += trade_condition_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OptionsTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

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

    offset += trade_condition_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OptionsTradeMessage::encoded_size() const {
    return wire_size;
}

void OptionsTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsTradeMessage::clone() const {
    return std::make_unique<OptionsTradeMessage>(*this);
}

void OptionsTradeMessage::print(std::ostream& out) const {
    out << "OptionsTradeMessage{";
    out << "source_time=";
    out << source_time_;
    out << ", source_time_ns=";
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
    out << ", trade_condition=";
    trade_condition_.print(out);
    out << '}';
}

bool OptionsTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsTradeMessage::operator==(const OptionsTradeMessage& other) const {
    return source_time_ == other.source_time_
        && source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && trade_condition_ == other.trade_condition_;
}

bool OptionsTradeMessage::operator!=(const OptionsTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
