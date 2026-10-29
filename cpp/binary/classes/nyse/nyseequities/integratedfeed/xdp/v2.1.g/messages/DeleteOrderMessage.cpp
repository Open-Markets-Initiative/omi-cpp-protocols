#include "DeleteOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

DeleteOrderMessage::DeleteOrderMessage(std::uint32_t source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint8_t num_parity_splits)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), num_parity_splits_(num_parity_splits) {}

std::uint32_t DeleteOrderMessage::source_time_ns() const { return source_time_ns_; }
void DeleteOrderMessage::set_source_time_ns(std::uint32_t value) { source_time_ns_ = value; }

std::uint32_t DeleteOrderMessage::symbol_index() const { return symbol_index_; }
void DeleteOrderMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t DeleteOrderMessage::symbol_seq_num() const { return symbol_seq_num_; }
void DeleteOrderMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t DeleteOrderMessage::order_id() const { return order_id_; }
void DeleteOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint8_t DeleteOrderMessage::num_parity_splits() const { return num_parity_splits_; }
void DeleteOrderMessage::set_num_parity_splits(std::uint8_t value) { num_parity_splits_ = value; }

MessageCode DeleteOrderMessage::type() const { return message_type; }

std::string_view DeleteOrderMessage::name() const { return "Delete Order Message"; }

std::size_t DeleteOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("DeleteOrderMessage", wire_size, length);

    source_time_ns_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    num_parity_splits_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t DeleteOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeleteOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_parity_splits_));
    offset += 1;

    return offset;
}

std::size_t DeleteOrderMessage::encoded_size() const {
    return wire_size;
}

void DeleteOrderMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> DeleteOrderMessage::clone() const {
    return std::make_unique<DeleteOrderMessage>(*this);
}

void DeleteOrderMessage::print(std::ostream& out) const {
    out << "DeleteOrderMessage{";
    out << "source_time_ns=";
    out << source_time_ns_;
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", num_parity_splits=";
    out << static_cast<int>(num_parity_splits_);
    out << '}';
}

bool DeleteOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const DeleteOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool DeleteOrderMessage::operator==(const DeleteOrderMessage& other) const {
    return source_time_ns_ == other.source_time_ns_
        && symbol_index_ == other.symbol_index_
        && symbol_seq_num_ == other.symbol_seq_num_
        && order_id_ == other.order_id_
        && num_parity_splits_ == other.num_parity_splits_;
}

bool DeleteOrderMessage::operator!=(const DeleteOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
