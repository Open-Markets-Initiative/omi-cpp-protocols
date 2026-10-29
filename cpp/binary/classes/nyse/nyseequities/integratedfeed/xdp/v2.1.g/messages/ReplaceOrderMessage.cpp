#include "ReplaceOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

ReplaceOrderMessage::ReplaceOrderMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint64_t new_order_id, std::uint32_t price, std::uint32_t volume, std::uint8_t prev_price_parity_splits, std::uint8_t new_price_parity_splits)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), new_order_id_(new_order_id), price_(price), volume_(volume), prev_price_parity_splits_(prev_price_parity_splits), new_price_parity_splits_(new_price_parity_splits) {}

std::uint32_t ReplaceOrderMessage::source_time_ns() const { return source_time_ns_; }
void ReplaceOrderMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t ReplaceOrderMessage::symbol_index() const { return symbol_index_; }
void ReplaceOrderMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t ReplaceOrderMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ReplaceOrderMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t ReplaceOrderMessage::order_id() const { return order_id_; }
void ReplaceOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint64_t ReplaceOrderMessage::new_order_id() const { return new_order_id_; }
void ReplaceOrderMessage::set_new_order_id(std::uint64_t value) { new_order_id_ = value; }

std::uint32_t ReplaceOrderMessage::price() const { return price_; }
void ReplaceOrderMessage::set_price(std::uint32_t value) { price_ = value; }

std::uint32_t ReplaceOrderMessage::volume() const { return volume_; }
void ReplaceOrderMessage::set_volume(std::uint32_t value) { volume_ = value; }

std::uint8_t ReplaceOrderMessage::prev_price_parity_splits() const { return prev_price_parity_splits_; }
void ReplaceOrderMessage::set_prev_price_parity_splits(std::uint8_t value) { prev_price_parity_splits_ = value; }

std::uint8_t ReplaceOrderMessage::new_price_parity_splits() const { return new_price_parity_splits_; }
void ReplaceOrderMessage::set_new_price_parity_splits(std::uint8_t value) { new_price_parity_splits_ = value; }

MessageCode ReplaceOrderMessage::type() const { return message_type; }

std::string_view ReplaceOrderMessage::name() const { return "Replace Order Message"; }

std::size_t ReplaceOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ReplaceOrderMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    new_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::read_u32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    prev_price_parity_splits_ = wire::read_u8(data + offset);
    offset += 1;

    new_price_parity_splits_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t ReplaceOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ReplaceOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(new_order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(prev_price_parity_splits_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(new_price_parity_splits_));
    offset += 1;

    return offset;
}

std::size_t ReplaceOrderMessage::encoded_size() const {
    return wire_size;
}

void ReplaceOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ReplaceOrderMessage::clone() const {
    return std::make_unique<ReplaceOrderMessage>(*this);
}

void ReplaceOrderMessage::print(std::ostream& out) const {
    out << "ReplaceOrderMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", new_order_id=";
    out << new_order_id_;
    out << ", price=";
    out << price_;
    out << ", volume=";
    out << volume_;
    out << ", prev_price_parity_splits=";
    out << static_cast<int>(prev_price_parity_splits_);
    out << ", new_price_parity_splits=";
    out << static_cast<int>(new_price_parity_splits_);
    out << '}';
}

bool ReplaceOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ReplaceOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ReplaceOrderMessage::operator==(const ReplaceOrderMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && order_id_ == other.order_id_
        && new_order_id_ == other.new_order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && prev_price_parity_splits_ == other.prev_price_parity_splits_
        && new_price_parity_splits_ == other.new_price_parity_splits_;
}

bool ReplaceOrderMessage::operator!=(const ReplaceOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
