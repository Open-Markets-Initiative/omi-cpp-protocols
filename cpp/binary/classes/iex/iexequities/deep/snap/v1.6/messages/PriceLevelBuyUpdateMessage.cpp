#include "PriceLevelBuyUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

PriceLevelBuyUpdateMessage::PriceLevelBuyUpdateMessage(EventFlags event_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t size, Decimal price)
  : event_flags_(event_flags), timestamp_(timestamp), symbol_(symbol), size_(size), price_(price) {}

EventFlags PriceLevelBuyUpdateMessage::event_flags() const { return event_flags_; }
void PriceLevelBuyUpdateMessage::set_event_flags(EventFlags value) { event_flags_ = value; }

std::chrono::nanoseconds PriceLevelBuyUpdateMessage::timestamp() const { return timestamp_; }
void PriceLevelBuyUpdateMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& PriceLevelBuyUpdateMessage::symbol() const { return symbol_; }
std::string& PriceLevelBuyUpdateMessage::symbol() { return symbol_; }
void PriceLevelBuyUpdateMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t PriceLevelBuyUpdateMessage::size() const { return size_; }
void PriceLevelBuyUpdateMessage::set_size(std::uint32_t value) { size_ = value; }

Decimal PriceLevelBuyUpdateMessage::price() const { return price_; }
void PriceLevelBuyUpdateMessage::set_price(Decimal value) { price_ = value; }

IexTpMessageDataCode PriceLevelBuyUpdateMessage::type() const { return message_type; }

std::string_view PriceLevelBuyUpdateMessage::name() const { return "Price Level Buy Update Message"; }

std::size_t PriceLevelBuyUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriceLevelBuyUpdateMessage", wire_size, length);

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

std::size_t PriceLevelBuyUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriceLevelBuyUpdateMessage", wire_size, capacity);

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

std::size_t PriceLevelBuyUpdateMessage::encoded_size() const {
    return wire_size;
}

void PriceLevelBuyUpdateMessage::accept(IexTpMessageDataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IexTpMessageData> PriceLevelBuyUpdateMessage::clone() const {
    return std::make_unique<PriceLevelBuyUpdateMessage>(*this);
}

void PriceLevelBuyUpdateMessage::print(std::ostream& out) const {
    out << "PriceLevelBuyUpdateMessage{";
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

bool PriceLevelBuyUpdateMessage::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const PriceLevelBuyUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PriceLevelBuyUpdateMessage::operator==(const PriceLevelBuyUpdateMessage& other) const {
    return event_flags_ == other.event_flags_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && size_ == other.size_
        && price_ == other.price_;
}

bool PriceLevelBuyUpdateMessage::operator!=(const PriceLevelBuyUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deep::snap::v1_6
