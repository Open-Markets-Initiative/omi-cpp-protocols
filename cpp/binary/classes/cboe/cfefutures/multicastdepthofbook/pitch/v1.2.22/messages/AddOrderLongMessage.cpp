#include "AddOrderLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

AddOrderLongMessage::AddOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity_long, const std::string& symbol, Decimal price_long)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_long_(quantity_long), symbol_(symbol), price_long_(price_long) {}

std::chrono::nanoseconds AddOrderLongMessage::time_offset() const { return time_offset_; }
void AddOrderLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AddOrderLongMessage::order_id() const { return order_id_; }
void AddOrderLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator AddOrderLongMessage::side_indicator() const { return side_indicator_; }
void AddOrderLongMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint32_t AddOrderLongMessage::quantity_long() const { return quantity_long_; }
void AddOrderLongMessage::set_quantity_long(std::uint32_t value) { quantity_long_ = value; }

const std::string& AddOrderLongMessage::symbol() const { return symbol_; }
std::string& AddOrderLongMessage::symbol() { return symbol_; }
void AddOrderLongMessage::set_symbol(const std::string& value) { symbol_ = value; }

Decimal AddOrderLongMessage::price_long() const { return price_long_; }
void AddOrderLongMessage::set_price_long(Decimal value) { price_long_ = value; }

MessageCode AddOrderLongMessage::type() const { return message_type; }

std::string_view AddOrderLongMessage::name() const { return "Add Order Long Message"; }

std::size_t AddOrderLongMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderLongMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_indicator_ = static_cast<SideIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t AddOrderLongMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderLongMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_indicator_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_long_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_long_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t AddOrderLongMessage::encoded_size() const {
    return wire_size;
}

void AddOrderLongMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderLongMessage::clone() const {
    return std::make_unique<AddOrderLongMessage>(*this);
}

void AddOrderLongMessage::print(std::ostream& out) const {
    out << "AddOrderLongMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side_indicator=";
    out << side_indicator_;
    out << ", quantity_long=";
    out << quantity_long_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", price_long=";
    out << price_long_;
    out << '}';
}

bool AddOrderLongMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderLongMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderLongMessage::operator==(const AddOrderLongMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && side_indicator_ == other.side_indicator_
        && quantity_long_ == other.quantity_long_
        && symbol_ == other.symbol_
        && price_long_ == other.price_long_;
}

bool AddOrderLongMessage::operator!=(const AddOrderLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
