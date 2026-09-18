#include "OrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

OrderDeleteMessage::OrderDeleteMessage(std::chrono::microseconds time_microseconds, std::uint32_t order_id, Side side, ModificationFlag modification_flag)
  : time_microseconds_(time_microseconds), order_id_(order_id), side_(side), modification_flag_(modification_flag) {}

std::chrono::microseconds OrderDeleteMessage::time_microseconds() const { return time_microseconds_; }
void OrderDeleteMessage::set_time_microseconds(std::chrono::microseconds value) { time_microseconds_ = value; }

std::uint32_t OrderDeleteMessage::order_id() const { return order_id_; }
void OrderDeleteMessage::set_order_id(std::uint32_t value) { order_id_ = value; }

Side OrderDeleteMessage::side() const { return side_; }
void OrderDeleteMessage::set_side(Side value) { side_ = value; }

ModificationFlag OrderDeleteMessage::modification_flag() const { return modification_flag_; }
void OrderDeleteMessage::set_modification_flag(ModificationFlag value) { modification_flag_ = value; }

MessageCode OrderDeleteMessage::type() const { return message_type; }

std::string_view OrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t OrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeleteMessage", wire_size, length);

    time_microseconds_ = std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    modification_flag_ = static_cast<ModificationFlag>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeleteMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_microseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(modification_flag_));
    offset += 1;

    return offset;
}

std::size_t OrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void OrderDeleteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderDeleteMessage::clone() const {
    return std::make_unique<OrderDeleteMessage>(*this);
}

void OrderDeleteMessage::print(std::ostream& out) const {
    out << "OrderDeleteMessage{";
    out << "time_microseconds=";
    out << time_microseconds_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", modification_flag=";
    out << modification_flag_;
    out << '}';
}

bool OrderDeleteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeleteMessage::operator==(const OrderDeleteMessage& other) const {
    return time_microseconds_ == other.time_microseconds_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && modification_flag_ == other.modification_flag_;
}

bool OrderDeleteMessage::operator!=(const OrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
