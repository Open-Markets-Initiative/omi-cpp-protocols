#include "AddOrderShortMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

AddOrderShortMessage::AddOrderShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint16_t quantity_short, const std::string& symbol, Decimal price_short)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_short_(quantity_short), symbol_(symbol), price_short_(price_short) {}

std::chrono::nanoseconds AddOrderShortMessage::time_offset() const { return time_offset_; }
void AddOrderShortMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AddOrderShortMessage::order_id() const { return order_id_; }
void AddOrderShortMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator AddOrderShortMessage::side_indicator() const { return side_indicator_; }
void AddOrderShortMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint16_t AddOrderShortMessage::quantity_short() const { return quantity_short_; }
void AddOrderShortMessage::set_quantity_short(std::uint16_t value) { quantity_short_ = value; }

const std::string& AddOrderShortMessage::symbol() const { return symbol_; }
std::string& AddOrderShortMessage::symbol() { return symbol_; }
void AddOrderShortMessage::set_symbol(const std::string& value) { symbol_ = value; }

Decimal AddOrderShortMessage::price_short() const { return price_short_; }
void AddOrderShortMessage::set_price_short(Decimal value) { price_short_ = value; }

MessageCode AddOrderShortMessage::type() const { return message_type; }

std::string_view AddOrderShortMessage::name() const { return "Add Order Short Message"; }

std::size_t AddOrderShortMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AddOrderShortMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_indicator_ = static_cast<SideIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_short_ = wire::read_u16_le(data + offset);
    offset += 2;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    price_short_ = Decimal(static_cast<std::int64_t>(wire::read_u16_le(data + offset)), -2);
    offset += 2;

    return offset;
}

std::size_t AddOrderShortMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AddOrderShortMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_indicator_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(quantity_short_));
    offset += 2;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(price_short_.mantissa()));
    offset += 2;

    return offset;
}

std::size_t AddOrderShortMessage::encoded_size() const {
    return wire_size;
}

void AddOrderShortMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> AddOrderShortMessage::clone() const {
    return std::make_unique<AddOrderShortMessage>(*this);
}

void AddOrderShortMessage::print(std::ostream& out) const {
    out << "AddOrderShortMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side_indicator=";
    out << side_indicator_;
    out << ", quantity_short=";
    out << quantity_short_;
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", price_short=";
    out << price_short_;
    out << '}';
}

bool AddOrderShortMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const AddOrderShortMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool AddOrderShortMessage::operator==(const AddOrderShortMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && side_indicator_ == other.side_indicator_
        && quantity_short_ == other.quantity_short_
        && symbol_ == other.symbol_
        && price_short_ == other.price_short_;
}

bool AddOrderShortMessage::operator!=(const AddOrderShortMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
