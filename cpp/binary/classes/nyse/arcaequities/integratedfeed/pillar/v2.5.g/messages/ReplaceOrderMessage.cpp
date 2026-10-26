#include "ReplaceOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

ReplaceOrderMessage::ReplaceOrderMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::uint64_t new_order_id, std::int32_t price, std::uint32_t volume, Side side, const std::array<std::byte, 1>& reserved_1)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), new_order_id_(new_order_id), price_(price), volume_(volume), side_(side), reserved_1_(reserved_1) {}

std::chrono::nanoseconds ReplaceOrderMessage::source_time_ns() const { return source_time_ns_; }
void ReplaceOrderMessage::set_source_time_ns(std::chrono::nanoseconds value) { source_time_ns_ = value; }

std::uint32_t ReplaceOrderMessage::symbol_index() const { return symbol_index_; }
void ReplaceOrderMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t ReplaceOrderMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ReplaceOrderMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t ReplaceOrderMessage::order_id() const { return order_id_; }
void ReplaceOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint64_t ReplaceOrderMessage::new_order_id() const { return new_order_id_; }
void ReplaceOrderMessage::set_new_order_id(std::uint64_t value) { new_order_id_ = value; }

std::int32_t ReplaceOrderMessage::price() const { return price_; }
void ReplaceOrderMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t ReplaceOrderMessage::volume() const { return volume_; }
void ReplaceOrderMessage::set_volume(std::uint32_t value) { volume_ = value; }

Side ReplaceOrderMessage::side() const { return side_; }
void ReplaceOrderMessage::set_side(Side value) { side_ = value; }

const std::array<std::byte, 1>& ReplaceOrderMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& ReplaceOrderMessage::reserved_1() { return reserved_1_; }
void ReplaceOrderMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode ReplaceOrderMessage::type() const { return message_type; }

std::string_view ReplaceOrderMessage::name() const { return "Replace Order Message"; }

std::size_t ReplaceOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ReplaceOrderMessage", wire_size, length);

    source_time_ns_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    new_order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t ReplaceOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ReplaceOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(new_order_id_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
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
    out << source_time_ns_.count();
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
    out << ", side=";
    out << side_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
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
        && side_ == other.side_
        && reserved_1_ == other.reserved_1_;
}

bool ReplaceOrderMessage::operator!=(const ReplaceOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g
