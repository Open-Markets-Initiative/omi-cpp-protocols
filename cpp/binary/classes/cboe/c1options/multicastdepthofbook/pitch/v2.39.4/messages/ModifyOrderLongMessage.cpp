#include "ModifyOrderLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

ModifyOrderLongMessage::ModifyOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t long_quantity, Decimal long_price, const ModifyFlags& modify_flags)
  : time_offset_(time_offset), order_id_(order_id), long_quantity_(long_quantity), long_price_(long_price), modify_flags_(modify_flags) {}

std::chrono::nanoseconds ModifyOrderLongMessage::time_offset() const { return time_offset_; }
void ModifyOrderLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t ModifyOrderLongMessage::order_id() const { return order_id_; }
void ModifyOrderLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t ModifyOrderLongMessage::long_quantity() const { return long_quantity_; }
void ModifyOrderLongMessage::set_long_quantity(std::uint32_t value) { long_quantity_ = value; }

Decimal ModifyOrderLongMessage::long_price() const { return long_price_; }
void ModifyOrderLongMessage::set_long_price(Decimal value) { long_price_ = value; }

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

    long_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    long_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
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

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(long_quantity_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(long_price_.mantissa()));
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
    out << ", long_quantity=";
    out << long_quantity_;
    out << ", long_price=";
    out << long_price_;
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
        && long_quantity_ == other.long_quantity_
        && long_price_ == other.long_price_
        && modify_flags_ == other.modify_flags_;
}

bool ModifyOrderLongMessage::operator!=(const ModifyOrderLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
