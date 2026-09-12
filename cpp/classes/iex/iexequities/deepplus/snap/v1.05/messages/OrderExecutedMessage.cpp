#include "OrderExecutedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

OrderExecutedMessage::OrderExecutedMessage(const SaleConditionFlags& sale_condition_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint64_t order_id_reference, std::uint32_t size, Decimal price, std::uint64_t trade_id)
  : sale_condition_flags_(sale_condition_flags), timestamp_(timestamp), symbol_(symbol), order_id_reference_(order_id_reference), size_(size), price_(price), trade_id_(trade_id) {}

const SaleConditionFlags& OrderExecutedMessage::sale_condition_flags() const { return sale_condition_flags_; }
SaleConditionFlags& OrderExecutedMessage::sale_condition_flags() { return sale_condition_flags_; }
void OrderExecutedMessage::set_sale_condition_flags(const SaleConditionFlags& value) { sale_condition_flags_ = value; }

std::chrono::nanoseconds OrderExecutedMessage::timestamp() const { return timestamp_; }
void OrderExecutedMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& OrderExecutedMessage::symbol() const { return symbol_; }
std::string& OrderExecutedMessage::symbol() { return symbol_; }
void OrderExecutedMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t OrderExecutedMessage::order_id_reference() const { return order_id_reference_; }
void OrderExecutedMessage::set_order_id_reference(std::uint64_t value) { order_id_reference_ = value; }

std::uint32_t OrderExecutedMessage::size() const { return size_; }
void OrderExecutedMessage::set_size(std::uint32_t value) { size_ = value; }

Decimal OrderExecutedMessage::price() const { return price_; }
void OrderExecutedMessage::set_price(Decimal value) { price_ = value; }

std::uint64_t OrderExecutedMessage::trade_id() const { return trade_id_; }
void OrderExecutedMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

IexTpMessageDataCode OrderExecutedMessage::type() const { return message_type; }

std::string_view OrderExecutedMessage::name() const { return "Order Executed Message"; }

std::size_t OrderExecutedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedMessage", wire_size, length);

    offset += sale_condition_flags_.decode(data + offset, length - offset);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    order_id_reference_ = wire::read_u64_le(data + offset);
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    trade_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedMessage", wire_size, capacity);

    offset += sale_condition_flags_.encode(data + offset, capacity - offset);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_reference_));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    return offset;
}

std::size_t OrderExecutedMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedMessage::accept(IexTpMessageDataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IexTpMessageData> OrderExecutedMessage::clone() const {
    return std::make_unique<OrderExecutedMessage>(*this);
}

void OrderExecutedMessage::print(std::ostream& out) const {
    out << "OrderExecutedMessage{";
    out << "sale_condition_flags=";
    sale_condition_flags_.print(out);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", order_id_reference=";
    out << order_id_reference_;
    out << ", size=";
    out << size_;
    out << ", price=";
    out << price_;
    out << ", trade_id=";
    out << trade_id_;
    out << '}';
}

bool OrderExecutedMessage::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const OrderExecutedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedMessage::operator==(const OrderExecutedMessage& other) const {
    return sale_condition_flags_ == other.sale_condition_flags_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && order_id_reference_ == other.order_id_reference_
        && size_ == other.size_
        && price_ == other.price_
        && trade_id_ == other.trade_id_;
}

bool OrderExecutedMessage::operator!=(const OrderExecutedMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::snap::v1_05
