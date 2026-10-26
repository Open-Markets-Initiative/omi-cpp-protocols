#include "OrderExecutionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

OrderExecutionMessage::OrderExecutionMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t symbol_id, std::uint64_t order_id, std::uint64_t trade_id, Decimal price, std::uint32_t size, const OrderExecutionFlags& order_execution_flags)
  : nanoseconds_(nanoseconds), symbol_id_(symbol_id), order_id_(order_id), trade_id_(trade_id), price_(price), size_(size), order_execution_flags_(order_execution_flags) {}

std::chrono::nanoseconds OrderExecutionMessage::nanoseconds() const { return nanoseconds_; }
void OrderExecutionMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t OrderExecutionMessage::symbol_id() const { return symbol_id_; }
void OrderExecutionMessage::set_symbol_id(std::uint32_t value) { symbol_id_ = value; }

std::uint64_t OrderExecutionMessage::order_id() const { return order_id_; }
void OrderExecutionMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint64_t OrderExecutionMessage::trade_id() const { return trade_id_; }
void OrderExecutionMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

Decimal OrderExecutionMessage::price() const { return price_; }
void OrderExecutionMessage::set_price(Decimal value) { price_ = value; }

std::uint32_t OrderExecutionMessage::size() const { return size_; }
void OrderExecutionMessage::set_size(std::uint32_t value) { size_ = value; }

const OrderExecutionFlags& OrderExecutionMessage::order_execution_flags() const { return order_execution_flags_; }
OrderExecutionFlags& OrderExecutionMessage::order_execution_flags() { return order_execution_flags_; }
void OrderExecutionMessage::set_order_execution_flags(const OrderExecutionFlags& value) { order_execution_flags_ = value; }

DataCode OrderExecutionMessage::type() const { return message_type; }

std::string_view OrderExecutionMessage::name() const { return "Order Execution Message"; }

std::size_t OrderExecutionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutionMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    trade_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -6);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += order_execution_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderExecutionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(symbol_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    offset += order_execution_flags_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t OrderExecutionMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutionMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> OrderExecutionMessage::clone() const {
    return std::make_unique<OrderExecutionMessage>(*this);
}

void OrderExecutionMessage::print(std::ostream& out) const {
    out << "OrderExecutionMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", symbol_id=";
    out << symbol_id_;
    out << ", order_id=";
    out << order_id_;
    out << ", trade_id=";
    out << trade_id_;
    out << ", price=";
    out << price_;
    out << ", size=";
    out << size_;
    out << ", order_execution_flags=";
    order_execution_flags_.print(out);
    out << '}';
}

bool OrderExecutionMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const OrderExecutionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutionMessage::operator==(const OrderExecutionMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && symbol_id_ == other.symbol_id_
        && order_id_ == other.order_id_
        && trade_id_ == other.trade_id_
        && price_ == other.price_
        && size_ == other.size_
        && order_execution_flags_ == other.order_execution_flags_;
}

bool OrderExecutionMessage::operator!=(const OrderExecutionMessage& other) const {
    return !(*this == other);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
