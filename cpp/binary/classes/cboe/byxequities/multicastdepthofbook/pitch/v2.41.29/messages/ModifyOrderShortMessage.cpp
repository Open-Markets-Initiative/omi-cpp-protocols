#include "ModifyOrderShortMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

ModifyOrderShortMessage::ModifyOrderShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint16_t quantity_short, Decimal price_short, const ModifyOrderFlags& modify_order_flags)
  : time_offset_(time_offset), order_id_(order_id), quantity_short_(quantity_short), price_short_(price_short), modify_order_flags_(modify_order_flags) {}

std::chrono::nanoseconds ModifyOrderShortMessage::time_offset() const { return time_offset_; }
void ModifyOrderShortMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t ModifyOrderShortMessage::order_id() const { return order_id_; }
void ModifyOrderShortMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint16_t ModifyOrderShortMessage::quantity_short() const { return quantity_short_; }
void ModifyOrderShortMessage::set_quantity_short(std::uint16_t value) { quantity_short_ = value; }

Decimal ModifyOrderShortMessage::price_short() const { return price_short_; }
void ModifyOrderShortMessage::set_price_short(Decimal value) { price_short_ = value; }

const ModifyOrderFlags& ModifyOrderShortMessage::modify_order_flags() const { return modify_order_flags_; }
ModifyOrderFlags& ModifyOrderShortMessage::modify_order_flags() { return modify_order_flags_; }
void ModifyOrderShortMessage::set_modify_order_flags(const ModifyOrderFlags& value) { modify_order_flags_ = value; }

MessageCode ModifyOrderShortMessage::type() const { return message_type; }

std::string_view ModifyOrderShortMessage::name() const { return "Modify Order Short Message"; }

std::size_t ModifyOrderShortMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ModifyOrderShortMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    quantity_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_le(data + offset)), -2);
    offset += 2;

    offset += modify_order_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ModifyOrderShortMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ModifyOrderShortMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(quantity_short_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(price_short_.mantissa()));
    offset += 2;

    offset += modify_order_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ModifyOrderShortMessage::encoded_size() const {
    return wire_size;
}

void ModifyOrderShortMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ModifyOrderShortMessage::clone() const {
    return std::make_unique<ModifyOrderShortMessage>(*this);
}

void ModifyOrderShortMessage::print(std::ostream& out) const {
    out << "ModifyOrderShortMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", quantity_short=";
    out << quantity_short_;
    out << ", price_short=";
    out << price_short_;
    out << ", modify_order_flags=";
    modify_order_flags_.print(out);
    out << '}';
}

bool ModifyOrderShortMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ModifyOrderShortMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ModifyOrderShortMessage::operator==(const ModifyOrderShortMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && quantity_short_ == other.quantity_short_
        && price_short_ == other.price_short_
        && modify_order_flags_ == other.modify_order_flags_;
}

bool ModifyOrderShortMessage::operator!=(const ModifyOrderShortMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
