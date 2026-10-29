#include "NewOrderAddMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

NewOrderAddMessage::NewOrderAddMessage(std::chrono::nanoseconds timestamp, std::uint16_t symbol_id, std::uint64_t order_id, Side side, Decimal quantity, const std::string& symbol, Decimal price, const std::string& broker, char reserved_1)
  : timestamp_(timestamp), symbol_id_(symbol_id), order_id_(order_id), side_(side), quantity_(quantity), symbol_(symbol), price_(price), broker_(broker), reserved_1_(reserved_1) {}

std::chrono::nanoseconds NewOrderAddMessage::timestamp() const { return timestamp_; }
void NewOrderAddMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t NewOrderAddMessage::symbol_id() const { return symbol_id_; }
void NewOrderAddMessage::set_symbol_id(std::uint16_t value) { symbol_id_ = value; }

std::uint64_t NewOrderAddMessage::order_id() const { return order_id_; }
void NewOrderAddMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

Side NewOrderAddMessage::side() const { return side_; }
void NewOrderAddMessage::set_side(Side value) { side_ = value; }

Decimal NewOrderAddMessage::quantity() const { return quantity_; }
void NewOrderAddMessage::set_quantity(Decimal value) { quantity_ = value; }

const std::string& NewOrderAddMessage::symbol() const { return symbol_; }
std::string& NewOrderAddMessage::symbol() { return symbol_; }
void NewOrderAddMessage::set_symbol(const std::string& value) { symbol_ = value; }

Decimal NewOrderAddMessage::price() const { return price_; }
void NewOrderAddMessage::set_price(Decimal value) { price_ = value; }

const std::string& NewOrderAddMessage::broker() const { return broker_; }
std::string& NewOrderAddMessage::broker() { return broker_; }
void NewOrderAddMessage::set_broker(const std::string& value) { broker_ = value; }

char NewOrderAddMessage::reserved_1() const { return reserved_1_; }
void NewOrderAddMessage::set_reserved_1(char value) { reserved_1_ = value; }

MessageCode NewOrderAddMessage::type() const { return message_type; }

std::string_view NewOrderAddMessage::name() const { return "New Order Add Message"; }

std::size_t NewOrderAddMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NewOrderAddMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    symbol_id_ = wire::read_u16_le(data + offset);
    offset += 2;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    quantity_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    symbol_ = wire::read_text(data + offset, 11, ' ');
    offset += 11;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -6);
    offset += 8;

    broker_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    reserved_1_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t NewOrderAddMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NewOrderAddMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(symbol_id_));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(quantity_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 11, ' ', symbol_);
    offset += 11;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', broker_);
    offset += 3;

    wire::write_char(data + offset, reserved_1_);
    offset += 1;

    return offset;
}

std::size_t NewOrderAddMessage::encoded_size() const {
    return wire_size;
}

void NewOrderAddMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NewOrderAddMessage::clone() const {
    return std::make_unique<NewOrderAddMessage>(*this);
}

void NewOrderAddMessage::print(std::ostream& out) const {
    out << "NewOrderAddMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", quantity=";
    out << quantity_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", price=";
    out << price_;
    out << ", broker=";
    print::text(out, broker_);
    out << ", reserved_1=";
    print::character(out, reserved_1_);
    out << '}';
}

bool NewOrderAddMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NewOrderAddMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NewOrderAddMessage::operator==(const NewOrderAddMessage& other) const {
    return timestamp_ == other.timestamp_
        && symbol_id_ == other.symbol_id_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && quantity_ == other.quantity_
        && symbol_ == other.symbol_
        && price_ == other.price_
        && broker_ == other.broker_
        && reserved_1_ == other.reserved_1_;
}

bool NewOrderAddMessage::operator!=(const NewOrderAddMessage& other) const {
    return !(*this == other);
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
