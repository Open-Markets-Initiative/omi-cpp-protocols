#include "AddOrderShortMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

AddOrderShortMessage::AddOrderShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint16_t quantity_binary_2, const std::string& symbol_short, Decimal price_binary_short_price_2, const AddFlags& add_flags)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_binary_2_(quantity_binary_2), symbol_short_(symbol_short), price_binary_short_price_2_(price_binary_short_price_2), add_flags_(add_flags) {}

std::chrono::nanoseconds AddOrderShortMessage::time_offset() const { return time_offset_; }
void AddOrderShortMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t AddOrderShortMessage::order_id() const { return order_id_; }
void AddOrderShortMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator AddOrderShortMessage::side_indicator() const { return side_indicator_; }
void AddOrderShortMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint16_t AddOrderShortMessage::quantity_binary_2() const { return quantity_binary_2_; }
void AddOrderShortMessage::set_quantity_binary_2(std::uint16_t value) { quantity_binary_2_ = value; }

const std::string& AddOrderShortMessage::symbol_short() const { return symbol_short_; }
std::string& AddOrderShortMessage::symbol_short() { return symbol_short_; }
void AddOrderShortMessage::set_symbol_short(const std::string& value) { symbol_short_ = value; }

Decimal AddOrderShortMessage::price_binary_short_price_2() const { return price_binary_short_price_2_; }
void AddOrderShortMessage::set_price_binary_short_price_2(Decimal value) { price_binary_short_price_2_ = value; }

const AddFlags& AddOrderShortMessage::add_flags() const { return add_flags_; }
AddFlags& AddOrderShortMessage::add_flags() { return add_flags_; }
void AddOrderShortMessage::set_add_flags(const AddFlags& value) { add_flags_ = value; }

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

    quantity_binary_2_ = wire::read_u16_le(data + offset);
    offset += 2;

    symbol_short_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    price_binary_short_price_2_ = Decimal(static_cast<std::int64_t>(wire::read_u16_le(data + offset)), -2);
    offset += 2;

    offset += add_flags_.decode(data + offset, length - offset);

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

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(quantity_binary_2_));
    offset += 2;

    wire::write_text(data + offset, 6, ' ', symbol_short_);
    offset += 6;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(price_binary_short_price_2_.mantissa()));
    offset += 2;

    offset += add_flags_.encode(data + offset, capacity - offset);

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
    out << ", quantity_binary_2=";
    out << quantity_binary_2_;
    out << ", symbol_short=";
    print::text(out, symbol_short_);
    out << ", price_binary_short_price_2=";
    out << price_binary_short_price_2_;
    out << ", add_flags=";
    add_flags_.print(out);
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
        && quantity_binary_2_ == other.quantity_binary_2_
        && symbol_short_ == other.symbol_short_
        && price_binary_short_price_2_ == other.price_binary_short_price_2_
        && add_flags_ == other.add_flags_;
}

bool AddOrderShortMessage::operator!=(const AddOrderShortMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
