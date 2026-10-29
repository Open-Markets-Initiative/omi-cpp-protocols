#include "RetailPriceImprovementMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

RetailPriceImprovementMessage::RetailPriceImprovementMessage(std::chrono::nanoseconds time_offset, const std::string& symbol_long, RetailPriceImprovement retail_price_improvement)
  : time_offset_(time_offset), symbol_long_(symbol_long), retail_price_improvement_(retail_price_improvement) {}

std::chrono::nanoseconds RetailPriceImprovementMessage::time_offset() const { return time_offset_; }
void RetailPriceImprovementMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

const std::string& RetailPriceImprovementMessage::symbol_long() const { return symbol_long_; }
std::string& RetailPriceImprovementMessage::symbol_long() { return symbol_long_; }
void RetailPriceImprovementMessage::set_symbol_long(const std::string& value) { symbol_long_ = value; }

RetailPriceImprovement RetailPriceImprovementMessage::retail_price_improvement() const { return retail_price_improvement_; }
void RetailPriceImprovementMessage::set_retail_price_improvement(RetailPriceImprovement value) { retail_price_improvement_ = value; }

MessageCode RetailPriceImprovementMessage::type() const { return message_type; }

std::string_view RetailPriceImprovementMessage::name() const { return "Retail Price Improvement Message"; }

std::size_t RetailPriceImprovementMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetailPriceImprovementMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    symbol_long_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    retail_price_improvement_ = static_cast<RetailPriceImprovement>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t RetailPriceImprovementMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetailPriceImprovementMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', symbol_long_);
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(retail_price_improvement_));
    offset += 1;

    return offset;
}

std::size_t RetailPriceImprovementMessage::encoded_size() const {
    return wire_size;
}

void RetailPriceImprovementMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> RetailPriceImprovementMessage::clone() const {
    return std::make_unique<RetailPriceImprovementMessage>(*this);
}

void RetailPriceImprovementMessage::print(std::ostream& out) const {
    out << "RetailPriceImprovementMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", symbol_long=";
    print::text(out, symbol_long_);
    out << ", retail_price_improvement=";
    out << retail_price_improvement_;
    out << '}';
}

bool RetailPriceImprovementMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const RetailPriceImprovementMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetailPriceImprovementMessage::operator==(const RetailPriceImprovementMessage& other) const {
    return time_offset_ == other.time_offset_
        && symbol_long_ == other.symbol_long_
        && retail_price_improvement_ == other.retail_price_improvement_;
}

bool RetailPriceImprovementMessage::operator!=(const RetailPriceImprovementMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
