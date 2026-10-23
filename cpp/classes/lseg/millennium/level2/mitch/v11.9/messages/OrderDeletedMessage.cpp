#include "OrderDeletedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderDeletedMessage::OrderDeletedMessage(std::uint32_t nanosecond, std::uint64_t order_id, const OrderDeletedFlags& order_deleted_flags, std::uint32_t instrument_id)
  : nanosecond_(nanosecond), order_id_(order_id), order_deleted_flags_(order_deleted_flags), instrument_id_(instrument_id) {}

std::uint32_t OrderDeletedMessage::nanosecond() const { return nanosecond_; }
void OrderDeletedMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint64_t OrderDeletedMessage::order_id() const { return order_id_; }
void OrderDeletedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

const OrderDeletedFlags& OrderDeletedMessage::order_deleted_flags() const { return order_deleted_flags_; }
OrderDeletedFlags& OrderDeletedMessage::order_deleted_flags() { return order_deleted_flags_; }
void OrderDeletedMessage::set_order_deleted_flags(const OrderDeletedFlags& value) { order_deleted_flags_ = value; }

std::uint32_t OrderDeletedMessage::instrument_id() const { return instrument_id_; }
void OrderDeletedMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

MessageCode OrderDeletedMessage::type() const { return message_type; }

std::string_view OrderDeletedMessage::name() const { return "Order Deleted Message"; }

std::size_t OrderDeletedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeletedMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    offset += order_deleted_flags_.decode(data + offset, length - offset);

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderDeletedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeletedMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    offset += order_deleted_flags_.encode(data + offset, capacity - offset);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    return offset;
}

std::size_t OrderDeletedMessage::encoded_size() const {
    return wire_size;
}

void OrderDeletedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderDeletedMessage::clone() const {
    return std::make_unique<OrderDeletedMessage>(*this);
}

void OrderDeletedMessage::print(std::ostream& out) const {
    out << "OrderDeletedMessage{";
    out << "nanosecond=";
    out << nanosecond_;
    out << ", order_id=";
    out << order_id_;
    out << ", order_deleted_flags=";
    order_deleted_flags_.print(out);
    out << ", instrument_id=";
    out << instrument_id_;
    out << '}';
}

bool OrderDeletedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderDeletedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeletedMessage::operator==(const OrderDeletedMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && order_id_ == other.order_id_
        && order_deleted_flags_ == other.order_deleted_flags_
        && instrument_id_ == other.instrument_id_;
}

bool OrderDeletedMessage::operator!=(const OrderDeletedMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
