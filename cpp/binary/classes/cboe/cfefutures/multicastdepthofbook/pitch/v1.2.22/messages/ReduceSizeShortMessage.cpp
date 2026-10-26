#include "ReduceSizeShortMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

ReduceSizeShortMessage::ReduceSizeShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, std::uint16_t canceled_quantity_short)
  : time_offset_(time_offset), order_id_(order_id), canceled_quantity_short_(canceled_quantity_short) {}

std::chrono::nanoseconds ReduceSizeShortMessage::time_offset() const { return time_offset_; }
void ReduceSizeShortMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t ReduceSizeShortMessage::order_id() const { return order_id_; }
void ReduceSizeShortMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint16_t ReduceSizeShortMessage::canceled_quantity_short() const { return canceled_quantity_short_; }
void ReduceSizeShortMessage::set_canceled_quantity_short(std::uint16_t value) { canceled_quantity_short_ = value; }

MessageCode ReduceSizeShortMessage::type() const { return message_type; }

std::string_view ReduceSizeShortMessage::name() const { return "Reduce Size Short Message"; }

std::size_t ReduceSizeShortMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ReduceSizeShortMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    canceled_quantity_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    return offset;
}

std::size_t ReduceSizeShortMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ReduceSizeShortMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(canceled_quantity_short_));
    offset += 2;

    return offset;
}

std::size_t ReduceSizeShortMessage::encoded_size() const {
    return wire_size;
}

void ReduceSizeShortMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ReduceSizeShortMessage::clone() const {
    return std::make_unique<ReduceSizeShortMessage>(*this);
}

void ReduceSizeShortMessage::print(std::ostream& out) const {
    out << "ReduceSizeShortMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", canceled_quantity_short=";
    out << canceled_quantity_short_;
    out << '}';
}

bool ReduceSizeShortMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ReduceSizeShortMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ReduceSizeShortMessage::operator==(const ReduceSizeShortMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && canceled_quantity_short_ == other.canceled_quantity_short_;
}

bool ReduceSizeShortMessage::operator!=(const ReduceSizeShortMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
