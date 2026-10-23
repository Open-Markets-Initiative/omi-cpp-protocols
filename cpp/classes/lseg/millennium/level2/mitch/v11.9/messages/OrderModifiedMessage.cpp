#include "OrderModifiedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderModifiedMessage::OrderModifiedMessage(std::uint32_t nanosecond, std::uint64_t order_id, std::uint32_t new_quantity, std::int64_t new_price, const OrderModifiedFlags& order_modified_flags)
  : nanosecond_(nanosecond), order_id_(order_id), new_quantity_(new_quantity), new_price_(new_price), order_modified_flags_(order_modified_flags) {}

std::uint32_t OrderModifiedMessage::nanosecond() const { return nanosecond_; }
void OrderModifiedMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint64_t OrderModifiedMessage::order_id() const { return order_id_; }
void OrderModifiedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderModifiedMessage::new_quantity() const { return new_quantity_; }
void OrderModifiedMessage::set_new_quantity(std::uint32_t value) { new_quantity_ = value; }

std::int64_t OrderModifiedMessage::new_price() const { return new_price_; }
void OrderModifiedMessage::set_new_price(std::int64_t value) { new_price_ = value; }

const OrderModifiedFlags& OrderModifiedMessage::order_modified_flags() const { return order_modified_flags_; }
OrderModifiedFlags& OrderModifiedMessage::order_modified_flags() { return order_modified_flags_; }
void OrderModifiedMessage::set_order_modified_flags(const OrderModifiedFlags& value) { order_modified_flags_ = value; }

MessageCode OrderModifiedMessage::type() const { return message_type; }

std::string_view OrderModifiedMessage::name() const { return "Order Modified Message"; }

std::size_t OrderModifiedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderModifiedMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    new_quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    new_price_ = wire::read_i64_le(data + offset);
    offset += 8;

    offset += order_modified_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderModifiedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderModifiedMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(new_quantity_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(new_price_));
    offset += 8;

    offset += order_modified_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderModifiedMessage::encoded_size() const {
    return wire_size;
}

void OrderModifiedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderModifiedMessage::clone() const {
    return std::make_unique<OrderModifiedMessage>(*this);
}

void OrderModifiedMessage::print(std::ostream& out) const {
    out << "OrderModifiedMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", order_id=";
    out << order_id_;
    out << ", new_quantity=";
    out << new_quantity_;
    out << ", new_price=";
    out << new_price_;
    out << ", order_modified_flags=";
    order_modified_flags_.print(out);
    out << '}';
}

bool OrderModifiedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderModifiedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderModifiedMessage::operator==(const OrderModifiedMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && order_id_ == other.order_id_
        && new_quantity_ == other.new_quantity_
        && new_price_ == other.new_price_
        && order_modified_flags_ == other.order_modified_flags_;
}

bool OrderModifiedMessage::operator!=(const OrderModifiedMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
