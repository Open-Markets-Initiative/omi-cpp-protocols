#include "DeleteOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

DeleteOrderMessage::DeleteOrderMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, const std::array<std::byte, 1>& reserved_1)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), reserved_1_(reserved_1) {}

std::chrono::nanoseconds DeleteOrderMessage::source_time_ns() const { return source_time_ns_; }
void DeleteOrderMessage::set_source_time_ns(std::chrono::nanoseconds value) { source_time_ns_ = value; }

std::uint32_t DeleteOrderMessage::symbol_index() const { return symbol_index_; }
void DeleteOrderMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t DeleteOrderMessage::symbol_seq_num() const { return symbol_seq_num_; }
void DeleteOrderMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t DeleteOrderMessage::order_id() const { return order_id_; }
void DeleteOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

const std::array<std::byte, 1>& DeleteOrderMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& DeleteOrderMessage::reserved_1() { return reserved_1_; }
void DeleteOrderMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode DeleteOrderMessage::type() const { return message_type; }

std::string_view DeleteOrderMessage::name() const { return "Delete Order Message"; }

std::size_t DeleteOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("DeleteOrderMessage", wire_size, length);

    source_time_ns_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t DeleteOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeleteOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
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
    out << source_time_ns_.count();
    out << ", symbol_index=";
    out << symbol_index_;
    out << ", symbol_seq_num=";
    out << symbol_seq_num_;
    out << ", order_id=";
    out << order_id_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
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
        && reserved_1_ == other.reserved_1_;
}

bool DeleteOrderMessage::operator!=(const DeleteOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
