#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::microseconds time_microseconds, std::uint32_t order_id, Side side, std::uint64_t volume, std::uint32_t match_id)
  : time_microseconds_(time_microseconds), order_id_(order_id), side_(side), volume_(volume), match_id_(match_id) {}

std::chrono::microseconds OrderExecutedMessage::time_microseconds() const { return time_microseconds_; }
void OrderExecutedMessage::set_time_microseconds(std::chrono::microseconds value) { time_microseconds_ = value; }

std::uint32_t OrderExecutedMessage::order_id() const { return order_id_; }
void OrderExecutedMessage::set_order_id(std::uint32_t value) { order_id_ = value; }

Side OrderExecutedMessage::side() const { return side_; }
void OrderExecutedMessage::set_side(Side value) { side_ = value; }

std::uint64_t OrderExecutedMessage::volume() const { return volume_; }
void OrderExecutedMessage::set_volume(std::uint64_t value) { volume_ = value; }

std::uint32_t OrderExecutedMessage::match_id() const { return match_id_; }
void OrderExecutedMessage::set_match_id(std::uint32_t value) { match_id_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    time_microseconds_ = std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    volume_ = wire::read_u48_be(data + offset);
    offset += 6;

    match_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_microseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(volume_));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_id_));
    offset += 4;

    return offset;
}

std::size_t OrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedMessage::clone() const {
    return std::make_unique<OrderExecutedMessage>(*this);
}

void OrderExecutedMessage::print(std::ostream& out) const {
    out << "OrderExecutedMessage{";
    out << "time_microseconds=";
    out << time_microseconds_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", volume=";
    out << volume_;
    out << ", match_id=";
    out << match_id_;
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return time_microseconds_ == other.time_microseconds_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && volume_ == other.volume_
        && match_id_ == other.match_id_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
