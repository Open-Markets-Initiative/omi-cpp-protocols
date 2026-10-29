#include "TradeLongMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

TradeLongMessage::TradeLongMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity, const std::string& symbol_short, Decimal price, std::uint64_t execution_id)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_(quantity), symbol_short_(symbol_short), price_(price), execution_id_(execution_id) {}

std::chrono::nanoseconds TradeLongMessage::time_offset() const { return time_offset_; }
void TradeLongMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t TradeLongMessage::order_id() const { return order_id_; }
void TradeLongMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator TradeLongMessage::side_indicator() const { return side_indicator_; }
void TradeLongMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint32_t TradeLongMessage::quantity() const { return quantity_; }
void TradeLongMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

const std::string& TradeLongMessage::symbol_short() const { return symbol_short_; }
std::string& TradeLongMessage::symbol_short() { return symbol_short_; }
void TradeLongMessage::set_symbol_short(const std::string& value) { symbol_short_ = value; }

Decimal TradeLongMessage::price() const { return price_; }
void TradeLongMessage::set_price(Decimal value) { price_ = value; }

std::uint64_t TradeLongMessage::execution_id() const { return execution_id_; }
void TradeLongMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

MessageCode TradeLongMessage::type() const { return message_type; }

std::string_view TradeLongMessage::name() const { return "Trade Long Message"; }

std::size_t TradeLongMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeLongMessage", wire_size, length);

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

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeLongMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeLongMessage", wire_size, capacity);

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

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    return offset;
}

std::size_t TradeLongMessage::encoded_size() const {
    return wire_size;
}

void TradeLongMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeLongMessage::clone() const {
    return std::make_unique<TradeLongMessage>(*this);
}

void TradeLongMessage::print(std::ostream& out) const {
    out << "TradeLongMessage{";
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
    out << ", execution_id=";
    out << execution_id_;
    out << '}';
}

bool TradeLongMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeLongMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeLongMessage::operator==(const TradeLongMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && side_indicator_ == other.side_indicator_
        && quantity_ == other.quantity_
        && symbol_short_ == other.symbol_short_
        && price_ == other.price_
        && execution_id_ == other.execution_id_;
}

bool TradeLongMessage::operator!=(const TradeLongMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29
