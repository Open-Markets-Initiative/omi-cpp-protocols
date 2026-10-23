#include "CrossTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

CrossTradeMessage::CrossTradeMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint32_t cross_id, std::uint32_t price, std::uint32_t volume, CrossType cross_type)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), cross_id_(cross_id), price_(price), volume_(volume), cross_type_(cross_type) {}

std::uint32_t CrossTradeMessage::source_time_ns() const { return source_time_ns_; }
void CrossTradeMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t CrossTradeMessage::symbol_index() const { return symbol_index_; }
void CrossTradeMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t CrossTradeMessage::symbol_seq_num() const { return symbol_seq_num_; }
void CrossTradeMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint32_t CrossTradeMessage::cross_id() const { return cross_id_; }
void CrossTradeMessage::set_cross_id(std::uint32_t value) { cross_id_ = value; }

std::uint32_t CrossTradeMessage::price() const { return price_; }
void CrossTradeMessage::set_price(std::uint32_t value) { price_ = value; }

std::uint32_t CrossTradeMessage::volume() const { return volume_; }
void CrossTradeMessage::set_volume(std::uint32_t value) { volume_ = value; }

CrossType CrossTradeMessage::cross_type() const { return cross_type_; }
void CrossTradeMessage::set_cross_type(CrossType value) { cross_type_ = value; }

MessageCode CrossTradeMessage::type() const { return message_type; }

std::string_view CrossTradeMessage::name() const { return "Cross Trade Message"; }

std::size_t CrossTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CrossTradeMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    cross_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = wire::read_u32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t CrossTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossTradeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(cross_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    return offset;
}

std::size_t CrossTradeMessage::encoded_size() const {
    return wire_size;
}

void CrossTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CrossTradeMessage::clone() const {
    return std::make_unique<CrossTradeMessage>(*this);
}

void CrossTradeMessage::print(std::ostream& out) const {
    out << "CrossTradeMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
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

bool CrossTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CrossTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CrossTradeMessage::operator==(const CrossTradeMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && cross_id_ == other.cross_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && cross_type_ == other.cross_type_;
}

bool CrossTradeMessage::operator!=(const CrossTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
