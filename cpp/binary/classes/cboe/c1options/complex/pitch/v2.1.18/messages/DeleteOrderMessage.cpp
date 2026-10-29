#include "DeleteOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

DeleteOrderMessage::DeleteOrderMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id)
  : time_offset_(time_offset), order_id_(order_id) {}

std::chrono::nanoseconds DeleteOrderMessage::time_offset() const { return time_offset_; }
void DeleteOrderMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t DeleteOrderMessage::order_id() const { return order_id_; }
void DeleteOrderMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

MessageCode DeleteOrderMessage::type() const { return message_type; }

std::string_view DeleteOrderMessage::name() const { return "Delete Order Message"; }

std::size_t DeleteOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("DeleteOrderMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t DeleteOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeleteOrderMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

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
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << '}';
}

bool DeleteOrderMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const DeleteOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool DeleteOrderMessage::operator==(const DeleteOrderMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_;
}

bool DeleteOrderMessage::operator!=(const DeleteOrderMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
