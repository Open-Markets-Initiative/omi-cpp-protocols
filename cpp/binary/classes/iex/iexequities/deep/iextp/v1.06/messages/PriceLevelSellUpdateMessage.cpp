#include "PriceLevelSellUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

PriceLevelSellUpdateMessage::PriceLevelSellUpdateMessage(EventFlags event_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t size, Decimal price)
  : event_flags_(event_flags), timestamp_(timestamp), symbol_(symbol), size_(size), price_(price) {}

EventFlags PriceLevelSellUpdateMessage::event_flags() const { return event_flags_; }
void PriceLevelSellUpdateMessage::set_event_flags(EventFlags value) { event_flags_ = value; }

std::chrono::nanoseconds PriceLevelSellUpdateMessage::timestamp() const { return timestamp_; }
void PriceLevelSellUpdateMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& PriceLevelSellUpdateMessage::symbol() const { return symbol_; }
std::string& PriceLevelSellUpdateMessage::symbol() { return symbol_; }
void PriceLevelSellUpdateMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t PriceLevelSellUpdateMessage::size() const { return size_; }
void PriceLevelSellUpdateMessage::set_size(std::uint32_t value) { size_ = value; }

Decimal PriceLevelSellUpdateMessage::price() const { return price_; }
void PriceLevelSellUpdateMessage::set_price(Decimal value) { price_ = value; }

MessageCode PriceLevelSellUpdateMessage::type() const { return message_type; }

std::string_view PriceLevelSellUpdateMessage::name() const { return "Price Level Sell Update Message"; }

std::size_t PriceLevelSellUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriceLevelSellUpdateMessage", wire_size, length);

    event_flags_ = static_cast<EventFlags>(wire::read_u8(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t PriceLevelSellUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriceLevelSellUpdateMessage", wire_size, capacity);

    wire::write_u8(data + offset, static_cast<std::uint8_t>(event_flags_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t PriceLevelSellUpdateMessage::encoded_size() const {
    return wire_size;
}

void PriceLevelSellUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PriceLevelSellUpdateMessage::clone() const {
    return std::make_unique<PriceLevelSellUpdateMessage>(*this);
}

void PriceLevelSellUpdateMessage::print(std::ostream& out) const {
    out << "PriceLevelSellUpdateMessage{";
    out << "event_flags=";
    out << event_flags_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", size=";
    out << size_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool PriceLevelSellUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PriceLevelSellUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PriceLevelSellUpdateMessage::operator==(const PriceLevelSellUpdateMessage& other) const {
    return event_flags_ == other.event_flags_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && size_ == other.size_
        && price_ == other.price_;
}

bool PriceLevelSellUpdateMessage::operator!=(const PriceLevelSellUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deep::iextp::v1_06
