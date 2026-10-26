#include "OrderAddedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

OrderAddedMessage::OrderAddedMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t order_id, Side side, std::uint32_t quantity, Decimal price)
  : timestamp_(timestamp), security_id_(security_id), order_id_(order_id), side_(side), quantity_(quantity), price_(price) {}

std::chrono::nanoseconds OrderAddedMessage::timestamp() const { return timestamp_; }
void OrderAddedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderAddedMessage::security_id() const { return security_id_; }
void OrderAddedMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

std::uint64_t OrderAddedMessage::order_id() const { return order_id_; }
void OrderAddedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Side OrderAddedMessage::side() const { return side_; }
void OrderAddedMessage::set_side(Side value) { side_ = value; }

std::uint32_t OrderAddedMessage::quantity() const { return quantity_; }
void OrderAddedMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

Decimal OrderAddedMessage::price() const { return price_; }
void OrderAddedMessage::set_price(Decimal value) { price_ = value; }

PayloadCode OrderAddedMessage::type() const { return message_type; }

std::string_view OrderAddedMessage::name() const { return "Order Added Message"; }

std::size_t OrderAddedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderAddedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t OrderAddedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderAddedMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OrderAddedMessage::encoded_size() const {
    return wire_size;
}

void OrderAddedMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> OrderAddedMessage::clone() const {
    return std::make_unique<OrderAddedMessage>(*this);
}

void OrderAddedMessage::print(std::ostream& out) const {
    out << "OrderAddedMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool OrderAddedMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const OrderAddedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderAddedMessage::operator==(const OrderAddedMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && quantity_ == other.quantity_
        && price_ == other.price_;
}

bool OrderAddedMessage::operator!=(const OrderAddedMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
