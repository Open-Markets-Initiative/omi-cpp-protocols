#include "ModifyOrderLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

ModifyOrderLongMessage::ModifyOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t quantity_long, Decimal price_long)
  : time_offset_(time_offset), order_id_(order_id), quantity_long_(quantity_long), price_long_(price_long) {}

std::chrono::nanoseconds ModifyOrderLongMessage::time_offset() const { return time_offset_; }
void ModifyOrderLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t ModifyOrderLongMessage::order_id() const { return order_id_; }
void ModifyOrderLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t ModifyOrderLongMessage::quantity_long() const { return quantity_long_; }
void ModifyOrderLongMessage::set_quantity_long(std::uint32_t value) { quantity_long_ = value; }

Decimal ModifyOrderLongMessage::price_long() const { return price_long_; }
void ModifyOrderLongMessage::set_price_long(Decimal value) { price_long_ = value; }

MessageCode ModifyOrderLongMessage::type() const { return message_type; }

std::string_view ModifyOrderLongMessage::name() const { return "Modify Order Long Message"; }

std::size_t ModifyOrderLongMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ModifyOrderLongMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    quantity_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t ModifyOrderLongMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ModifyOrderLongMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_long_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_long_.mantissa()));
    offset += 8;

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
    out << ", quantity_long=";
    out << quantity_long_;
    out << ", price_long=";
    out << price_long_;
    out << '}';
}

bool ModifyOrderLongMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ModifyOrderLongMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ModifyOrderLongMessage::operator==(const ModifyOrderLongMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && quantity_long_ == other.quantity_long_
        && price_long_ == other.price_long_;
}

bool ModifyOrderLongMessage::operator!=(const ModifyOrderLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
