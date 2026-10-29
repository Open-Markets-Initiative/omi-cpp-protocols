#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds timestamp, std::uint64_t order_id, Decimal quantity, std::uint64_t execution_id, Side side, Decimal price, const std::string& broker, const std::string& contra_broker)
  : timestamp_(timestamp), order_id_(order_id), quantity_(quantity), execution_id_(execution_id), side_(side), price_(price), broker_(broker), contra_broker_(contra_broker) {}

std::chrono::nanoseconds OrderExecutedMessage::timestamp() const { return timestamp_; }
void OrderExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t OrderExecutedMessage::order_id() const { return order_id_; }
void OrderExecutedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Decimal OrderExecutedMessage::quantity() const { return quantity_; }
void OrderExecutedMessage::set_quantity(Decimal value) { quantity_ = value; }

std::uint64_t OrderExecutedMessage::execution_id() const { return execution_id_; }
void OrderExecutedMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

Side OrderExecutedMessage::side() const { return side_; }
void OrderExecutedMessage::set_side(Side value) { side_ = value; }

Decimal OrderExecutedMessage::price() const { return price_; }
void OrderExecutedMessage::set_price(Decimal value) { price_ = value; }

const std::string& OrderExecutedMessage::broker() const { return broker_; }
std::string& OrderExecutedMessage::broker() { return broker_; }
void OrderExecutedMessage::set_broker(const std::string& value) { broker_ = value; }

const std::string& OrderExecutedMessage::contra_broker() const { return contra_broker_; }
std::string& OrderExecutedMessage::contra_broker() { return contra_broker_; }
void OrderExecutedMessage::set_contra_broker(const std::string& value) { contra_broker_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    quantity_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    broker_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    contra_broker_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quantity_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', broker_);
    offset += 3;

    wire::write_text(data + offset, 3, ' ', contra_broker_);
    offset += 3;

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
    out << "timestamp=";
    out << timestamp_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", quantity=";
    out << quantity_;
    out << ", execution_id=";
    out << execution_id_;
    out << ", side=";
    out << side_;
    out << ", price=";
    out << price_;
    out << ", broker=";
    print::text(out, broker_);
    out << ", contra_broker=";
    print::text(out, contra_broker_);
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_id_ == other.order_id_
        && quantity_ == other.quantity_
        && execution_id_ == other.execution_id_
        && side_ == other.side_
        && price_ == other.price_
        && broker_ == other.broker_
        && contra_broker_ == other.contra_broker_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
