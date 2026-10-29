#include "TradeShortMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

TradeShortMessage::TradeShortMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint16_t quantity_binary_2, const std::string& symbol_short, Decimal price_binary_short_price_2, std::uint64_t execution_id)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_binary_2_(quantity_binary_2), symbol_short_(symbol_short), price_binary_short_price_2_(price_binary_short_price_2), execution_id_(execution_id) {}

std::chrono::nanoseconds TradeShortMessage::time_offset() const { return time_offset_; }
void TradeShortMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t TradeShortMessage::order_id() const { return order_id_; }
void TradeShortMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator TradeShortMessage::side_indicator() const { return side_indicator_; }
void TradeShortMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint16_t TradeShortMessage::quantity_binary_2() const { return quantity_binary_2_; }
void TradeShortMessage::set_quantity_binary_2(std::uint16_t value) { quantity_binary_2_ = value; }

const std::string& TradeShortMessage::symbol_short() const { return symbol_short_; }
std::string& TradeShortMessage::symbol_short() { return symbol_short_; }
void TradeShortMessage::set_symbol_short(const std::string& value) { symbol_short_ = value; }

Decimal TradeShortMessage::price_binary_short_price_2() const { return price_binary_short_price_2_; }
void TradeShortMessage::set_price_binary_short_price_2(Decimal value) { price_binary_short_price_2_ = value; }

std::uint64_t TradeShortMessage::execution_id() const { return execution_id_; }
void TradeShortMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

MessageCode TradeShortMessage::type() const { return message_type; }

std::string_view TradeShortMessage::name() const { return "Trade Short Message"; }

std::size_t TradeShortMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeShortMessage", wire_size, length);

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

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeShortMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeShortMessage", wire_size, capacity);

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

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    return offset;
}

std::size_t TradeShortMessage::encoded_size() const {
    return wire_size;
}

void TradeShortMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeShortMessage::clone() const {
    return std::make_unique<TradeShortMessage>(*this);
}

void TradeShortMessage::print(std::ostream& out) const {
    out << "TradeShortMessage{";
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
    out << ", execution_id=";
    out << execution_id_;
    out << '}';
}

bool TradeShortMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeShortMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeShortMessage::operator==(const TradeShortMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && side_indicator_ == other.side_indicator_
        && quantity_binary_2_ == other.quantity_binary_2_
        && symbol_short_ == other.symbol_short_
        && price_binary_short_price_2_ == other.price_binary_short_price_2_
        && execution_id_ == other.execution_id_;
}

bool TradeShortMessage::operator!=(const TradeShortMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
