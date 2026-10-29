#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

OrderExecutedMessage::OrderExecutedMessage(std::chrono::nanoseconds timestamp, std::uint32_t order_token, std::uint32_t executed_quantity, Decimal execution_price, LiquidityIndicator liquidity_indicator, std::uint64_t match_number)
  : timestamp_(timestamp), order_token_(order_token), executed_quantity_(executed_quantity), execution_price_(execution_price), liquidity_indicator_(liquidity_indicator), match_number_(match_number) {}

std::chrono::nanoseconds OrderExecutedMessage::timestamp() const { return timestamp_; }
void OrderExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderExecutedMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint32_t OrderExecutedMessage::order_token() const { return order_token_; }
void OrderExecutedMessage::set_order_token(std::uint32_t value) { order_token_ = value; }

std::uint32_t OrderExecutedMessage::executed_quantity() const { return executed_quantity_; }
void OrderExecutedMessage::set_executed_quantity(std::uint32_t value) { executed_quantity_ = value; }

Decimal OrderExecutedMessage::execution_price() const { return execution_price_; }
void OrderExecutedMessage::set_execution_price(Decimal value) { execution_price_ = value; }

LiquidityIndicator OrderExecutedMessage::liquidity_indicator() const { return liquidity_indicator_; }
void OrderExecutedMessage::set_liquidity_indicator(LiquidityIndicator value) { liquidity_indicator_ = value; }

std::uint64_t OrderExecutedMessage::match_number() const { return match_number_; }
void OrderExecutedMessage::set_match_number(std::uint64_t value) { match_number_ = value; }

SequencedMessageCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    executed_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    execution_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    liquidity_indicator_ = static_cast<LiquidityIndicator>(wire::read_char(data + offset));
    offset += 1;

    match_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_token_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(executed_quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(execution_price_.mantissa()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(liquidity_indicator_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(match_number_));
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderExecutedMessage::clone() const {
    return std::make_unique<OrderExecutedMessage>(*this);
}

void OrderExecutedMessage::print(std::ostream& out) const {
    out << "OrderExecutedMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "Asia/Tokyo");
    out << ", order_token=";
    out << order_token_;
    out << ", executed_quantity=";
    out << executed_quantity_;
    out << ", execution_price=";
    out << execution_price_;
    out << ", liquidity_indicator=";
    out << liquidity_indicator_;
    out << ", match_number=";
    out << match_number_;
    out << '}';
}

bool OrderExecutedMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return timestamp_ == other.timestamp_
        && order_token_ == other.order_token_
        && executed_quantity_ == other.executed_quantity_
        && execution_price_ == other.execution_price_
        && liquidity_indicator_ == other.liquidity_indicator_
        && match_number_ == other.match_number_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
