#include "OptionsCrossTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

OptionsCrossTradeMessage::OptionsCrossTradeMessage(std::uint32_t source_time_ns, std::uint32_t series_index, std::uint32_t series_seq_num, std::uint32_t cross_id, std::int32_t price, std::uint32_t volume, CrossType cross_type)
  : source_time_ns_(source_time_ns), series_index_(series_index), series_seq_num_(series_seq_num), cross_id_(cross_id), price_(price), volume_(volume), cross_type_(cross_type) {}

std::uint32_t OptionsCrossTradeMessage::source_time_ns() const { return source_time_ns_; }
void OptionsCrossTradeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t OptionsCrossTradeMessage::series_index() const { return series_index_; }
void OptionsCrossTradeMessage::set_series_index(std::uint32_t value) { series_index_ = value; }

std::uint32_t OptionsCrossTradeMessage::series_seq_num() const { return series_seq_num_; }
void OptionsCrossTradeMessage::set_series_seq_num(std::uint32_t value) { series_seq_num_ = value; }

std::uint32_t OptionsCrossTradeMessage::cross_id() const { return cross_id_; }
void OptionsCrossTradeMessage::set_cross_id(std::uint32_t value) { cross_id_ = value; }

std::int32_t OptionsCrossTradeMessage::price() const { return price_; }
void OptionsCrossTradeMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t OptionsCrossTradeMessage::volume() const { return volume_; }
void OptionsCrossTradeMessage::set_volume(std::uint32_t value) { volume_ = value; }

CrossType OptionsCrossTradeMessage::cross_type() const { return cross_type_; }
void OptionsCrossTradeMessage::set_cross_type(CrossType value) { cross_type_ = value; }

MessageCode OptionsCrossTradeMessage::type() const { return message_type; }

std::string_view OptionsCrossTradeMessage::name() const { return "Options Cross Trade Message"; }

std::size_t OptionsCrossTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OptionsCrossTradeMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    series_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    cross_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OptionsCrossTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionsCrossTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(series_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(cross_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    return offset;
}

std::size_t OptionsCrossTradeMessage::encoded_size() const {
    return wire_size;
}

void OptionsCrossTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OptionsCrossTradeMessage::clone() const {
    return std::make_unique<OptionsCrossTradeMessage>(*this);
}

void OptionsCrossTradeMessage::print(std::ostream& out) const {
    out << "OptionsCrossTradeMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", series_index=";
    out << series_index_;
    out << ", series_seq_num=";
    out << series_seq_num_;
    out << ", cross_id=";
    out << cross_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", cross_type=";
    out << cross_type_;
    out << '}';
}

bool OptionsCrossTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OptionsCrossTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OptionsCrossTradeMessage::operator==(const OptionsCrossTradeMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && series_index_ == other.series_index_
        && series_seq_num_ == other.series_seq_num_
        && cross_id_ == other.cross_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && cross_type_ == other.cross_type_;
}

bool OptionsCrossTradeMessage::operator!=(const OptionsCrossTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
