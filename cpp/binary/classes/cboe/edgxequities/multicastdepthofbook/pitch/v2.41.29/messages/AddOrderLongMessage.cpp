#include "AddOrderLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

AddOrderLongMessage::AddOrderLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity, const std::string& symbol_short, Decimal price, const AddOrderFlags& add_order_flags)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_(quantity), symbol_short_(symbol_short), price_(price), add_order_flags_(add_order_flags) {}

std::chrono::nanoseconds AddOrderLongMessage::time_offset() const { return time_offset_; }
void AddOrderLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AddOrderLongMessage::order_id() const { return order_id_; }
void AddOrderLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator AddOrderLongMessage::side_indicator() const { return side_indicator_; }
void AddOrderLongMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint32_t AddOrderLongMessage::quantity() const { return quantity_; }
void AddOrderLongMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

const std::string& AddOrderLongMessage::symbol_short() const { return symbol_short_; }
std::string& AddOrderLongMessage::symbol_short() { return symbol_short_; }
void AddOrderLongMessage::set_symbol_short(const std::string& value) { symbol_short_ = value; }

Decimal AddOrderLongMessage::price() const { return price_; }
void AddOrderLongMessage::set_price(Decimal value) { price_ = value; }

const AddOrderFlags& AddOrderLongMessage::add_order_flags() const { return add_order_flags_; }
AddOrderFlags& AddOrderLongMessage::add_order_flags() { return add_order_flags_; }
void AddOrderLongMessage::set_add_order_flags(const AddOrderFlags& value) { add_order_flags_ = value; }

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

    quantity_ = wire::read_u32_le(data + offset);
    offset += 4;

    symbol_short_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    offset += add_order_flags_.decode(data + offset, length - offset);

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

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_short_);
    offset += 6;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_.mantissa()));
    offset += 8;

    offset += add_order_flags_.encode(data + offset, capacity - offset);

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
    out << ", quantity=";
    out << quantity_;
    out << ", symbol_short=";
    print::text(out, symbol_short_);
    out << ", price=";
    out << price_;
    out << ", add_order_flags=";
    add_order_flags_.print(out);
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
        && quantity_ == other.quantity_
        && symbol_short_ == other.symbol_short_
        && price_ == other.price_
        && add_order_flags_ == other.add_order_flags_;
}

bool AddOrderLongMessage::operator!=(const AddOrderLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29
