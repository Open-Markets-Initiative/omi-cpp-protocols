#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Side side, std::uint64_t order_id, std::uint32_t quantity_remaining, TradeType trade_type, std::uint64_t trade_id, std::uint32_t executed_quantity, Decimal trade_price, std::uint64_t combination_trade_id, const std::string& counter_party_id)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), side_(side), order_id_(order_id), quantity_remaining_(quantity_remaining), trade_type_(trade_type), trade_id_(trade_id), executed_quantity_(executed_quantity), trade_price_(trade_price), combination_trade_id_(combination_trade_id), counter_party_id_(counter_party_id) {}

std::chrono::nanoseconds OrderExecutedMessage::nanoseconds() const { return nanoseconds_; }
void OrderExecutedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t OrderExecutedMessage::trade_date() const { return trade_date_; }
void OrderExecutedMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t OrderExecutedMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void OrderExecutedMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

Side OrderExecutedMessage::side() const { return side_; }
void OrderExecutedMessage::set_side(Side value) { side_ = value; }

std::uint64_t OrderExecutedMessage::order_id() const { return order_id_; }
void OrderExecutedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint32_t OrderExecutedMessage::quantity_remaining() const { return quantity_remaining_; }
void OrderExecutedMessage::set_quantity_remaining(std::uint32_t value) { quantity_remaining_ = value; }

TradeType OrderExecutedMessage::trade_type() const { return trade_type_; }
void OrderExecutedMessage::set_trade_type(TradeType value) { trade_type_ = value; }

std::uint64_t OrderExecutedMessage::trade_id() const { return trade_id_; }
void OrderExecutedMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

std::uint32_t OrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

Decimal OrderExecutedMessage::trade_price() const { return trade_price_; }
void OrderExecutedMessage::set_trade_price(Decimal value) { trade_price_ = value; }

std::uint64_t OrderExecutedMessage::combination_trade_id() const { return combination_trade_id_; }
void OrderExecutedMessage::set_combination_trade_id(std::uint64_t value) { combination_trade_id_ = value; }

const std::string& OrderExecutedMessage::counter_party_id() const { return counter_party_id_; }
std::string& OrderExecutedMessage::counter_party_id() { return counter_party_id_; }
void OrderExecutedMessage::set_counter_party_id(const std::string& value) { counter_party_id_ = value; }

MessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    quantity_remaining_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_type_ = static_cast<TradeType>(wire::read_char(data + offset));
    offset += 1;

    trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    executed_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    trade_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    combination_trade_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    counter_party_id_ = wire::read_text(data + offset, 3, ' ');
    offset += 3;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_remaining_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(trade_type_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(trade_price_.mantissa()));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(combination_trade_id_));
    offset += 8;

    wire::write_text(data + offset, 3, ' ', counter_party_id_);
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
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", side=";
    out << side_;
    out << ", order_id=";
    out << order_id_;
    out << ", quantity_remaining=";
    out << quantity_remaining_;
    out << ", trade_type=";
    out << trade_type_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", trade_price=";
    out << trade_price_;
    out << ", combination_trade_id=";
    out << combination_trade_id_;
    out << ", counter_party_id=";
    print::text(out, counter_party_id_);
    out << '}';
}

bool OrderExecutedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && side_ == other.side_
        && order_id_ == other.order_id_
        && quantity_remaining_ == other.quantity_remaining_
        && trade_type_ == other.trade_type_
        && trade_id_ == other.trade_id_
        && executed_quantity_ == other.executed_quantity_
        && trade_price_ == other.trade_price_
        && combination_trade_id_ == other.combination_trade_id_
        && counter_party_id_ == other.counter_party_id_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
