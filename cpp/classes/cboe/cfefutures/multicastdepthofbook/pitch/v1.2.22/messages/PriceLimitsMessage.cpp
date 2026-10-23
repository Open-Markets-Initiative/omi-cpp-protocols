#include "PriceLimitsMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

PriceLimitsMessage::PriceLimitsMessage(std::chrono::nanoseconds time_offset, const std::string& symbol, Decimal upper_price_limit, Decimal lower_price_limit)
  : time_offset_(time_offset), symbol_(symbol), upper_price_limit_(upper_price_limit), lower_price_limit_(lower_price_limit) {}

std::chrono::nanoseconds PriceLimitsMessage::time_offset() const { return time_offset_; }
void PriceLimitsMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& PriceLimitsMessage::symbol() const { return symbol_; }
std::string& PriceLimitsMessage::symbol() { return symbol_; }
void PriceLimitsMessage::set_symbol(const std::string& value) { symbol_ = value; }

Decimal PriceLimitsMessage::upper_price_limit() const { return upper_price_limit_; }
void PriceLimitsMessage::set_upper_price_limit(Decimal value) { upper_price_limit_ = value; }

Decimal PriceLimitsMessage::lower_price_limit() const { return lower_price_limit_; }
void PriceLimitsMessage::set_lower_price_limit(Decimal value) { lower_price_limit_ = value; }

MessageCode PriceLimitsMessage::type() const { return message_type; }

std::string_view PriceLimitsMessage::name() const { return "Price Limits Message"; }

std::size_t PriceLimitsMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PriceLimitsMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    upper_price_limit_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    lower_price_limit_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    return offset;
}

std::size_t PriceLimitsMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PriceLimitsMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 6, ' ', symbol_);
    offset += 6;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(upper_price_limit_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(lower_price_limit_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t PriceLimitsMessage::encoded_size() const {
    return wire_size;
}

void PriceLimitsMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> PriceLimitsMessage::clone() const {
    return std::make_unique<PriceLimitsMessage>(*this);
}

void PriceLimitsMessage::print(std::ostream& out) const {
    out << "PriceLimitsMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", upper_price_limit=";
    out << upper_price_limit_;
    out << ", lower_price_limit=";
    out << lower_price_limit_;
    out << '}';
}

bool PriceLimitsMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const PriceLimitsMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PriceLimitsMessage::operator==(const PriceLimitsMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_ == other.symbol_
        && upper_price_limit_ == other.upper_price_limit_
        && lower_price_limit_ == other.lower_price_limit_;
}

bool PriceLimitsMessage::operator!=(const PriceLimitsMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
