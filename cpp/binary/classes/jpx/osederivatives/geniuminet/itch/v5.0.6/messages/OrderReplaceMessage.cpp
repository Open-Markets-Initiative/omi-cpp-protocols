#include "OrderReplaceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

OrderReplaceMessage::OrderReplaceMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t order_id, std::uint32_t order_book_id, Side side, std::uint32_t new_orderbook_position, std::uint64_t quantity, std::int32_t price, const OrderAttributes& order_attributes)
  : nanoseconds_(nanoseconds), order_id_(order_id), order_book_id_(order_book_id), side_(side), new_orderbook_position_(new_orderbook_position), quantity_(quantity), price_(price), order_attributes_(order_attributes) {}

std::chrono::nanoseconds OrderReplaceMessage::nanoseconds() const { return nanoseconds_; }
void OrderReplaceMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderReplaceMessage::order_id() const { return order_id_; }
void OrderReplaceMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderReplaceMessage::order_book_id() const { return order_book_id_; }
void OrderReplaceMessage::set_order_book_id(std::uint32_t value) { order_book_id_ = value; }

Side OrderReplaceMessage::side() const { return side_; }
void OrderReplaceMessage::set_side(Side value) { side_ = value; }

std::uint32_t OrderReplaceMessage::new_orderbook_position() const { return new_orderbook_position_; }
void OrderReplaceMessage::set_new_orderbook_position(std::uint32_t value) { new_orderbook_position_ = value; }

std::uint64_t OrderReplaceMessage::quantity() const { return quantity_; }
void OrderReplaceMessage::set_quantity(std::uint64_t value) { quantity_ = value; }

std::int32_t OrderReplaceMessage::price() const { return price_; }
void OrderReplaceMessage::set_price(std::int32_t value) { price_ = value; }

const OrderAttributes& OrderReplaceMessage::order_attributes() const { return order_attributes_; }
OrderAttributes& OrderReplaceMessage::order_attributes() { return order_attributes_; }
void OrderReplaceMessage::set_order_attributes(const OrderAttributes& value) { order_attributes_ = value; }

MessageCode OrderReplaceMessage::type() const { return message_type; }

std::string_view OrderReplaceMessage::name() const { return "Order Replace Message"; }

std::size_t OrderReplaceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderReplaceMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    order_book_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    new_orderbook_position_ = wire::read_u32_be(data + offset);
    offset += 4;

    quantity_ = wire::read_u64_be(data + offset);
    offset += 8;

    price_ = wire::read_i32_be(data + offset);
    offset += 4;

    offset += order_attributes_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderReplaceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderReplaceMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(new_orderbook_position_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(quantity_));
    offset += 8;

    wire::write_i32_be(data + offset, static_cast<std::int32_t>(price_));
    offset += 4;

    offset += order_attributes_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderReplaceMessage::encoded_size() const {
    return wire_size;
}

void OrderReplaceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderReplaceMessage::clone() const {
    return std::make_unique<OrderReplaceMessage>(*this);
}

void OrderReplaceMessage::print(std::ostream& out) const {
    out << "OrderReplaceMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", order_book_id=";
    out << order_book_id_;
    out << ", side=";
    out << side_;
    out << ", new_orderbook_position=";
    out << new_orderbook_position_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << ", order_attributes=";
    order_attributes_.print(out);
    out << '}';
}

bool OrderReplaceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderReplaceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderReplaceMessage::operator==(const OrderReplaceMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && order_id_ == other.order_id_
        && order_book_id_ == other.order_book_id_
        && side_ == other.side_
        && new_orderbook_position_ == other.new_orderbook_position_
        && quantity_ == other.quantity_
        && price_ == other.price_
        && order_attributes_ == other.order_attributes_;
}

bool OrderReplaceMessage::operator!=(const OrderReplaceMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
