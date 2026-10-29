#include "ModifyOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

ModifyOrderMessage::ModifyOrderMessage(std::chrono::nanoseconds source_time_ns, std::uint32_t symbol_index, std::uint32_t symbol_seq_num, std::uint64_t order_id, std::int32_t price, std::uint32_t volume, std::uint8_t position_change, Side side, const std::array<std::byte, 1>& reserved_1)
  : source_time_ns_(source_time_ns), symbol_index_(symbol_index), symbol_seq_num_(symbol_seq_num), order_id_(order_id), price_(price), volume_(volume), position_change_(position_change), side_(side), reserved_1_(reserved_1) {}

std::chrono::nanoseconds ModifyOrderMessage::source_time_ns() const { return source_time_ns_; }
void ModifyOrderMessage::set_source_time_ns(std::chrono::nanoseconds value) { source_time_ns_ = value; }

std::uint32_t ModifyOrderMessage::symbol_index() const { return symbol_index_; }
void ModifyOrderMessage::set_symbol_index(std::uint32_t value) { symbol_index_ = value; }

std::uint32_t ModifyOrderMessage::symbol_seq_num() const { return symbol_seq_num_; }
void ModifyOrderMessage::set_symbol_seq_num(std::uint32_t value) { symbol_seq_num_ = value; }

std::uint64_t ModifyOrderMessage::order_id() const { return order_id_; }
void ModifyOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::int32_t ModifyOrderMessage::price() const { return price_; }
void ModifyOrderMessage::set_price(std::int32_t value) { price_ = value; }

std::uint32_t ModifyOrderMessage::volume() const { return volume_; }
void ModifyOrderMessage::set_volume(std::uint32_t value) { volume_ = value; }

std::uint8_t ModifyOrderMessage::position_change() const { return position_change_; }
void ModifyOrderMessage::set_position_change(std::uint8_t value) { position_change_ = value; }

Side ModifyOrderMessage::side() const { return side_; }
void ModifyOrderMessage::set_side(Side value) { side_ = value; }

const std::array<std::byte, 1>& ModifyOrderMessage::reserved_1() const { return reserved_1_; }
std::array<std::byte, 1>& ModifyOrderMessage::reserved_1() { return reserved_1_; }
void ModifyOrderMessage::set_reserved_1(const std::array<std::byte, 1>& value) { reserved_1_ = value; }

MessageCode ModifyOrderMessage::type() const { return message_type; }

std::string_view ModifyOrderMessage::name() const { return "Modify Order Message"; }

std::size_t ModifyOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ModifyOrderMessage", wire_size, length);

    source_time_ns_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_index_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_seq_num_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = wire::read_i32_le(data + offset);
    offset += 4;

    volume_ = wire::read_u32_le(data + offset);
    offset += 4;

    position_change_ = wire::read_u8(data + offset);
    offset += 1;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_1_.data(), 1);
    offset += 1;

    return offset;
}

std::size_t ModifyOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ModifyOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_ns_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_index_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_seq_num_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(volume_));
    offset += 4;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(position_change_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_1_.data(), 1);
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
    out << source_time_ns_.count();
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
    out << static_cast<int>(position_change_);
    out << ", side=";
    out << side_;
    out << ", reserved_1=";
    print::hex(out, reserved_1_.data(), reserved_1_.size());
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
        && side_ == other.side_
        && reserved_1_ == other.reserved_1_;
}

bool ModifyOrderMessage::operator!=(const ModifyOrderMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
