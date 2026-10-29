#include "ModifyOrderLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

ModifyOrderLongMessage::ModifyOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t quantity, Decimal price, const ModifyOrderFlags& modify_order_flags)
  : time_offset_(time_offset), order_id_(order_id), quantity_(quantity), price_(price), modify_order_flags_(modify_order_flags) {}

std::chrono::nanoseconds ModifyOrderLongMessage::time_offset() const { return time_offset_; }
void ModifyOrderLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t ModifyOrderLongMessage::order_id() const { return order_id_; }
void ModifyOrderLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t ModifyOrderLongMessage::quantity() const { return quantity_; }
void ModifyOrderLongMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

Decimal ModifyOrderLongMessage::price() const { return price_; }
void ModifyOrderLongMessage::set_price(Decimal value) { price_ = value; }

const ModifyOrderFlags& ModifyOrderLongMessage::modify_order_flags() const { return modify_order_flags_; }
ModifyOrderFlags& ModifyOrderLongMessage::modify_order_flags() { return modify_order_flags_; }
void ModifyOrderLongMessage::set_modify_order_flags(const ModifyOrderFlags& value) { modify_order_flags_ = value; }

MessageCode ModifyOrderLongMessage::type() const { return message_type; }

std::string_view ModifyOrderLongMessage::name() const { return "Modify Order Long Message"; }

std::size_t ModifyOrderLongMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ModifyOrderLongMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    offset += modify_order_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ModifyOrderLongMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ModifyOrderLongMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    offset += modify_order_flags_.encode(data + offset, capacity - offset);

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
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << ", modify_order_flags=";
    modify_order_flags_.print(out);
    out << '}';
}

bool ModifyOrderLongMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ModifyOrderLongMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ModifyOrderLongMessage::operator==(const ModifyOrderLongMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && quantity_ == other.quantity_
        && price_ == other.price_
        && modify_order_flags_ == other.modify_order_flags_;
}

bool ModifyOrderLongMessage::operator!=(const ModifyOrderLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29
