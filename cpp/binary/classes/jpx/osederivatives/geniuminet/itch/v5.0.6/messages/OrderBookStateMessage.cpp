#include "OrderBookStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

OrderBookStateMessage::OrderBookStateMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t order_book_id, const std::string& state_name)
  : nanoseconds_(nanoseconds), order_book_id_(order_book_id), state_name_(state_name) {}

std::chrono::nanoseconds OrderBookStateMessage::nanoseconds() const { return nanoseconds_; }
void OrderBookStateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t OrderBookStateMessage::order_book_id() const { return order_book_id_; }
void OrderBookStateMessage::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

const std::string& OrderBookStateMessage::state_name() const { return state_name_; }
std::string& OrderBookStateMessage::state_name() { return state_name_; }
void OrderBookStateMessage::set_state_name(const std::string& value) { state_name_ = value; }

MessageCode OrderBookStateMessage::type() const { return message_type; }

std::string_view OrderBookStateMessage::name() const { return "Order Book State Message"; }

std::size_t OrderBookStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookStateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    state_name_ = wire::read_text(data + offset, 20, ' ');
    offset += 20;

    return offset;
}

std::size_t OrderBookStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookStateMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_text(data + offset, 20, ' ', state_name_);
    offset += 20;

    return offset;
}

std::size_t OrderBookStateMessage::encoded_size() const {
    return wire_size;
}

void OrderBookStateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookStateMessage::clone() const {
    return std::make_unique<OrderBookStateMessage>(*this);
}

void OrderBookStateMessage::print(std::ostream& out) const {
    out << "OrderBookStateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", state_name=";
    print::text(out, state_name_);
    out << '}';
}

bool OrderBookStateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookStateMessage::operator==(const OrderBookStateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_book_id_ == other.order_book_id_
        && state_name_ == other.state_name_;
}

bool OrderBookStateMessage::operator!=(const OrderBookStateMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
