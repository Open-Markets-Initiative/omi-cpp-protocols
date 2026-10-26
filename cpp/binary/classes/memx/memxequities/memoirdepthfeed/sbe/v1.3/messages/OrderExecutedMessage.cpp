#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds timestamp, std::uint16_t security_id, std::uint64_t order_id, std::uint64_t trade_id, std::uint32_t quantity, Decimal price)
  : timestamp_(timestamp), security_id_(security_id), order_id_(order_id), trade_id_(trade_id), quantity_(quantity), price_(price) {}

std::chrono::nanoseconds OrderExecutedMessage::timestamp() const { return timestamp_; }
void OrderExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderExecutedMessage::security_id() const { return security_id_; }
void OrderExecutedMessage::set_security_id(std::uint16_t value) { security_id_ = value; }

std::uint64_t OrderExecutedMessage::order_id() const { return order_id_; }
void OrderExecutedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint64_t OrderExecutedMessage::trade_id() const { return trade_id_; }
void OrderExecutedMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t OrderExecutedMessage::quantity() const { return quantity_; }
void OrderExecutedMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

Decimal OrderExecutedMessage::price() const { return price_; }
void OrderExecutedMessage::set_price(Decimal value) { price_ = value; }

PayloadCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    security_id_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -6);
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(security_id_));
    offset += 2;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedMessage::accept(PayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Payload> OrderExecutedMessage::clone() const {
    return std::make_unique<OrderExecutedMessage>(*this);
}

void OrderExecutedMessage::print(std::ostream& out) const {
    out << "OrderExecutedMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", security_id=";
    out << security_id_;
    out << ", order_id=";
    out << order_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool OrderExecutedMessage::equals(const Payload& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return timestamp_ == other.timestamp_
        && security_id_ == other.security_id_
        && order_id_ == other.order_id_
        && trade_id_ == other.trade_id_
        && quantity_ == other.quantity_
        && price_ == other.price_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
