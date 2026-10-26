#include "ReduceSizeLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

ReduceSizeLongMessage::ReduceSizeLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint32_t canceled_quantity_long)
  : time_offset_(time_offset), order_id_(order_id), canceled_quantity_long_(canceled_quantity_long) {}

std::chrono::nanoseconds ReduceSizeLongMessage::time_offset() const { return time_offset_; }
void ReduceSizeLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t ReduceSizeLongMessage::order_id() const { return order_id_; }
void ReduceSizeLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t ReduceSizeLongMessage::canceled_quantity_long() const { return canceled_quantity_long_; }
void ReduceSizeLongMessage::set_canceled_quantity_long(std::uint32_t value) { canceled_quantity_long_ = value; }

MessageCode ReduceSizeLongMessage::type() const { return message_type; }

std::string_view ReduceSizeLongMessage::name() const { return "Reduce Size Long Message"; }

std::size_t ReduceSizeLongMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ReduceSizeLongMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    canceled_quantity_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t ReduceSizeLongMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ReduceSizeLongMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(canceled_quantity_long_));
    offset += 4;

    return offset;
}

std::size_t ReduceSizeLongMessage::encoded_size() const {
    return wire_size;
}

void ReduceSizeLongMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ReduceSizeLongMessage::clone() const {
    return std::make_unique<ReduceSizeLongMessage>(*this);
}

void ReduceSizeLongMessage::print(std::ostream& out) const {
    out << "ReduceSizeLongMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", canceled_quantity_long=";
    out << canceled_quantity_long_;
    out << '}';
}

bool ReduceSizeLongMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ReduceSizeLongMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ReduceSizeLongMessage::operator==(const ReduceSizeLongMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && canceled_quantity_long_ == other.canceled_quantity_long_;
}

bool ReduceSizeLongMessage::operator!=(const ReduceSizeLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
