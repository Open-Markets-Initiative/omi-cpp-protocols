#include "ModifyOrderLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

ModifyOrderLongMessage::ModifyOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t quantity_binary_4, Decimal price_binary_long_price_8, const ModifyFlags& modify_flags)
  : time_offset_(time_offset), order_id_(order_id), quantity_binary_4_(quantity_binary_4), price_binary_long_price_8_(price_binary_long_price_8), modify_flags_(modify_flags) {}

std::chrono::nanoseconds ModifyOrderLongMessage::time_offset() const { return time_offset_; }
void ModifyOrderLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t ModifyOrderLongMessage::order_id() const { return order_id_; }
void ModifyOrderLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t ModifyOrderLongMessage::quantity_binary_4() const { return quantity_binary_4_; }
void ModifyOrderLongMessage::set_quantity_binary_4(std::uint32_t value) { quantity_binary_4_ = value; }

Decimal ModifyOrderLongMessage::price_binary_long_price_8() const { return price_binary_long_price_8_; }
void ModifyOrderLongMessage::set_price_binary_long_price_8(Decimal value) { price_binary_long_price_8_ = value; }

const ModifyFlags& ModifyOrderLongMessage::modify_flags() const { return modify_flags_; }
ModifyFlags& ModifyOrderLongMessage::modify_flags() { return modify_flags_; }
void ModifyOrderLongMessage::set_modify_flags(const ModifyFlags& value) { modify_flags_ = value; }

MessageCode ModifyOrderLongMessage::type() const { return message_type; }

std::string_view ModifyOrderLongMessage::name() const { return "Modify Order Long Message"; }

std::size_t ModifyOrderLongMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ModifyOrderLongMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    quantity_binary_4_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_binary_long_price_8_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    offset += modify_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ModifyOrderLongMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ModifyOrderLongMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_binary_4_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_binary_long_price_8_.mantissa()));
    offset += 8;

    offset += modify_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ModifyOrderLongMessage::encoded_size() const {
    return wire_size;
}

void ModifyOrderLongMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ModifyOrderLongMessage::clone() const {
    return std::make_unique<ModifyOrderLongMessage>(*this);
}

void ModifyOrderLongMessage::print(std::ostream& out) const {
    out << "ModifyOrderLongMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", quantity_binary_4=";
    out << quantity_binary_4_;
    out << ", price_binary_long_price_8=";
    out << price_binary_long_price_8_;
    out << ", modify_flags=";
    modify_flags_.print(out);
    out << '}';
}

bool ModifyOrderLongMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ModifyOrderLongMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ModifyOrderLongMessage::operator==(const ModifyOrderLongMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && quantity_binary_4_ == other.quantity_binary_4_
        && price_binary_long_price_8_ == other.price_binary_long_price_8_
        && modify_flags_ == other.modify_flags_;
}

bool ModifyOrderLongMessage::operator!=(const ModifyOrderLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
