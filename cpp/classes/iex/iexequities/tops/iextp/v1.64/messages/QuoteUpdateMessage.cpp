#include "QuoteUpdateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::tops::iextp::v1_64 {

QuoteUpdateMessage::QuoteUpdateMessage(const QuoteUpdateFlags& quote_update_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t bid_size, Decimal bid_price, Decimal ask_price, std::uint32_t ask_size)
  : quote_update_flags_(quote_update_flags), timestamp_(timestamp), symbol_(symbol), bid_size_(bid_size), bid_price_(bid_price), ask_price_(ask_price), ask_size_(ask_size) {}

const QuoteUpdateFlags& QuoteUpdateMessage::quote_update_flags() const { return quote_update_flags_; }
QuoteUpdateFlags& QuoteUpdateMessage::quote_update_flags() { return quote_update_flags_; }
void QuoteUpdateMessage::set_quote_update_flags(const QuoteUpdateFlags& value) { quote_update_flags_ = value; }

std::chrono::nanoseconds QuoteUpdateMessage::timestamp() const { return timestamp_; }
void QuoteUpdateMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& QuoteUpdateMessage::symbol() const { return symbol_; }
std::string& QuoteUpdateMessage::symbol() { return symbol_; }
void QuoteUpdateMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t QuoteUpdateMessage::bid_size() const { return bid_size_; }
void QuoteUpdateMessage::set_bid_size(std::uint32_t value) { bid_size_ = value; }

Decimal QuoteUpdateMessage::bid_price() const { return bid_price_; }
void QuoteUpdateMessage::set_bid_price(Decimal value) { bid_price_ = value; }

Decimal QuoteUpdateMessage::ask_price() const { return ask_price_; }
void QuoteUpdateMessage::set_ask_price(Decimal value) { ask_price_ = value; }

std::uint32_t QuoteUpdateMessage::ask_size() const { return ask_size_; }
void QuoteUpdateMessage::set_ask_size(std::uint32_t value) { ask_size_ = value; }

MessageCode QuoteUpdateMessage::type() const { return message_type; }

std::string_view QuoteUpdateMessage::name() const { return "Quote Update Message"; }

std::size_t QuoteUpdateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("QuoteUpdateMessage", wire_size, length);

    offset += quote_update_flags_.decode(data + offset, length - offset);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    bid_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    bid_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    ask_price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    ask_size_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t QuoteUpdateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("QuoteUpdateMessage", wire_size, capacity);

    offset += quote_update_flags_.encode(data + offset, capacity - offset);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(bid_size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(bid_price_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(ask_price_.mantissa()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(ask_size_));
    offset += 4;

    return offset;
}

std::size_t QuoteUpdateMessage::encoded_size() const {
    return wire_size;
}

void QuoteUpdateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> QuoteUpdateMessage::clone() const {
    return std::make_unique<QuoteUpdateMessage>(*this);
}

void QuoteUpdateMessage::print(std::ostream& out) const {
    out << "QuoteUpdateMessage{";
    out << "quote_update_flags=";
    quote_update_flags_.print(out);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", bid_size=";
    out << bid_size_;
    out << ", bid_price=";
    out << bid_price_;
    out << ", ask_price=";
    out << ask_price_;
    out << ", ask_size=";
    out << ask_size_;
    out << '}';
}

bool QuoteUpdateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const QuoteUpdateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool QuoteUpdateMessage::operator==(const QuoteUpdateMessage& other) const {
    return quote_update_flags_ == other.quote_update_flags_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && bid_size_ == other.bid_size_
        && bid_price_ == other.bid_price_
        && ask_price_ == other.ask_price_
        && ask_size_ == other.ask_size_;
}

bool QuoteUpdateMessage::operator!=(const QuoteUpdateMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::tops::iextp::v1_64
