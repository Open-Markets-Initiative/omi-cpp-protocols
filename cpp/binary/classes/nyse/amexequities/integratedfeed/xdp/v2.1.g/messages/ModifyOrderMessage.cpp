#include "ModifyOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

ModifyOrderMessage::ModifyOrderMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint32_t price, std::uint32_t volume, PositionChange position_change, std::uint8_t prev_price_parity_splits, std::uint8_t new_price_parity_splits)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), price_(price), volume_(volume), position_change_(position_change), prev_price_parity_splits_(prev_price_parity_splits), new_price_parity_splits_(new_price_parity_splits) {}

std::uint32_t ModifyOrderMessage::source_time_ns() const { return source_time_ns_; }
void ModifyOrderMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t ModifyOrderMessage::symbol_index() const { return symbol_index_; }
void ModifyOrderMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t ModifyOrderMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ModifyOrderMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t ModifyOrderMessage::order_id() const { return order_id_; }
void ModifyOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t ModifyOrderMessage::price() const { return price_; }
void ModifyOrderMessage::set_price(std::uint32_t value) { price_ = value; }

std::uint32_t ModifyOrderMessage::volume() const { return volume_; }
void ModifyOrderMessage::set_volume(std::uint32_t value) { volume_ = value; }

PositionChange ModifyOrderMessage::position_change() const { return position_change_; }
void ModifyOrderMessage::set_position_change(PositionChange value) { position_change_ = value; }

std::uint8_t ModifyOrderMessage::prev_price_parity_splits() const { return prev_price_parity_splits_; }
void ModifyOrderMessage::set_prev_price_parity_splits(std::uint8_t value) { prev_price_parity_splits_ = value; }

std::uint8_t ModifyOrderMessage::new_price_parity_splits() const { return new_price_parity_splits_; }
void ModifyOrderMessage::set_new_price_parity_splits(std::uint8_t value) { new_price_parity_splits_ = value; }

MessageCode ModifyOrderMessage::type() const { return message_type; }

std::string_view ModifyOrderMessage::name() const { return "Modify Order Message"; }

std::size_t ModifyOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ModifyOrderMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::read_u32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    position_change_ = static_cast<PositionChange>(wire::read_u8(data + offset));
    offset += 1;

    prev_price_parity_splits_ = wire::read_u8(data + offset);
    offset += 1;

    new_price_parity_splits_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t ModifyOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ModifyOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(position_change_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(prev_price_parity_splits_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(new_price_parity_splits_));
    offset += 1;

    return offset;
}

std::size_t ModifyOrderMessage::encoded_size() const {
    return wire_size;
}

void ModifyOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ModifyOrderMessage::clone() const {
    return std::make_unique<ModifyOrderMessage>(*this);
}

void ModifyOrderMessage::print(std::ostream& out) const {
    out << "ModifyOrderMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", position_change=";
    out << position_change_;
    out << ", prev_price_parity_splits=";
    out << static_cast<int>(prev_price_parity_splits_);
    out << ", new_price_parity_splits=";
    out << static_cast<int>(new_price_parity_splits_);
    out << '}';
}

bool ModifyOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ModifyOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ModifyOrderMessage::operator==(const ModifyOrderMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && position_change_ == other.position_change_
        && prev_price_parity_splits_ == other.prev_price_parity_splits_
        && new_price_parity_splits_ == other.new_price_parity_splits_;
}

bool ModifyOrderMessage::operator!=(const ModifyOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
