#include "OrderAiqCanceledMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

OrderAiqCanceledMessage::OrderAiqCanceledMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, std::uint32_t decrement_quantity, OrderCanceledReason order_canceled_reason, std::uint32_t quantity_prevented_from_trading, Decimal execution_price, LiquidityIndicator liquidity_indicator)
  : timestamp_(timestamp), order_token_(order_token), decrement_quantity_(decrement_quantity), order_canceled_reason_(order_canceled_reason), quantity_prevented_from_trading_(quantity_prevented_from_trading), execution_price_(execution_price), liquidity_indicator_(liquidity_indicator) {}

std::chrono::nanoseconds OrderAiqCanceledMessage::timestamp() const { return timestamp_; }
void OrderAiqCanceledMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderAiqCanceledMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t OrderAiqCanceledMessage::order_token() const { return order_token_; }
void OrderAiqCanceledMessage::set_order_token(std::uint32_t value) { order_token_ = value; }

std::uint32_t OrderAiqCanceledMessage::decrement_quantity() const { return decrement_quantity_; }
void OrderAiqCanceledMessage::set_decrement_quantity(std::uint32_t value) { decrement_quantity_ = value; }

OrderCanceledReason OrderAiqCanceledMessage::order_canceled_reason() const { return order_canceled_reason_; }
void OrderAiqCanceledMessage::set_order_canceled_reason(OrderCanceledReason value) { order_canceled_reason_ = value; }

std::uint32_t OrderAiqCanceledMessage::quantity_prevented_from_trading() const { return quantity_prevented_from_trading_; }
void OrderAiqCanceledMessage::set_quantity_prevented_from_trading(std::uint32_t value) { quantity_prevented_from_trading_ = value; }

Decimal OrderAiqCanceledMessage::execution_price() const { return execution_price_; }
void OrderAiqCanceledMessage::set_execution_price(Decimal value) { execution_price_ = value; }

LiquidityIndicator OrderAiqCanceledMessage::liquidity_indicator() const { return liquidity_indicator_; }
void OrderAiqCanceledMessage::set_liquidity_indicator(LiquidityIndicator value) { liquidity_indicator_ = value; }

SequencedMessageCode OrderAiqCanceledMessage::type() const { return message_type; }

std::string_view OrderAiqCanceledMessage::name() const { return "Order Aiq Canceled Message"; }

std::size_t OrderAiqCanceledMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderAiqCanceledMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    decrement_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_canceled_reason_ = static_cast<OrderCanceledReason>(wire::read_char(data + offset));
    offset += 1;

    quantity_prevented_from_trading_ = wire::read_u32_be(data + offset);
    offset += 4;

    execution_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    liquidity_indicator_ = static_cast<LiquidityIndicator>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderAiqCanceledMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderAiqCanceledMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_token_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(decrement_quantity_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(order_canceled_reason_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_prevented_from_trading_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(execution_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(liquidity_indicator_));
    offset += 1;

    return offset;
}

std::size_t OrderAiqCanceledMessage::encoded_size() const {
    return wire_size;
}

void OrderAiqCanceledMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderAiqCanceledMessage::clone() const {
    return std::make_unique<OrderAiqCanceledMessage>(*this);
}

void OrderAiqCanceledMessage::print(std::ostream& out) const {
    out << "OrderAiqCanceledMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "Asia/Tokyo");
    out << ", order_token=";
    out << order_token_;
    out << ", decrement_quantity=";
    out << decrement_quantity_;
    out << ", order_canceled_reason=";
    out << order_canceled_reason_;
    out << ", quantity_prevented_from_trading=";
    out << quantity_prevented_from_trading_;
    out << ", execution_price=";
    out << execution_price_;
    out << ", liquidity_indicator=";
    out << liquidity_indicator_;
    out << '}';
}

bool OrderAiqCanceledMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderAiqCanceledMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderAiqCanceledMessage::operator==(const OrderAiqCanceledMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_token_ == other.order_token_
        && decrement_quantity_ == other.decrement_quantity_
        && order_canceled_reason_ == other.order_canceled_reason_
        && quantity_prevented_from_trading_ == other.quantity_prevented_from_trading_
        && execution_price_ == other.execution_price_
        && liquidity_indicator_ == other.liquidity_indicator_;
}

bool OrderAiqCanceledMessage::operator!=(const OrderAiqCanceledMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
