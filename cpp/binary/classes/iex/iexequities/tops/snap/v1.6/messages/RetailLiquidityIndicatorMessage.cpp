#include "RetailLiquidityIndicatorMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

RetailLiquidityIndicatorMessage::RetailLiquidityIndicatorMessage(RetailLiquidityIndicator retail_liquidity_indicator, std::chrono::nanoseconds timestamp, const std::string& symbol)
  : retail_liquidity_indicator_(retail_liquidity_indicator), timestamp_(timestamp), symbol_(symbol) {}

RetailLiquidityIndicator RetailLiquidityIndicatorMessage::retail_liquidity_indicator() const { return retail_liquidity_indicator_; }
void RetailLiquidityIndicatorMessage::set_retail_liquidity_indicator(RetailLiquidityIndicator value) { retail_liquidity_indicator_ = value; }

std::chrono::nanoseconds RetailLiquidityIndicatorMessage::timestamp() const { return timestamp_; }
void RetailLiquidityIndicatorMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& RetailLiquidityIndicatorMessage::symbol() const { return symbol_; }
std::string& RetailLiquidityIndicatorMessage::symbol() { return symbol_; }
void RetailLiquidityIndicatorMessage::set_symbol(const std::string& value) { symbol_ = value; }

IexTpMessageDataCode RetailLiquidityIndicatorMessage::type() const { return message_type; }

std::string_view RetailLiquidityIndicatorMessage::name() const { return "Retail Liquidity Indicator Message"; }

std::size_t RetailLiquidityIndicatorMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("RetailLiquidityIndicatorMessage", wire_size, length);

    retail_liquidity_indicator_ = static_cast<RetailLiquidityIndicator>(wire::read_char(data + offset));
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    return offset;
}

std::size_t RetailLiquidityIndicatorMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RetailLiquidityIndicatorMessage", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(retail_liquidity_indicator_));
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    return offset;
}

std::size_t RetailLiquidityIndicatorMessage::encoded_size() const {
    return wire_size;
}

void RetailLiquidityIndicatorMessage::accept(IexTpMessageDataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<IexTpMessageData> RetailLiquidityIndicatorMessage::clone() const {
    return std::make_unique<RetailLiquidityIndicatorMessage>(*this);
}

void RetailLiquidityIndicatorMessage::print(std::ostream& out) const {
    out << "RetailLiquidityIndicatorMessage{";
    out << "retail_liquidity_indicator=";
    out << retail_liquidity_indicator_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << '}';
}

bool RetailLiquidityIndicatorMessage::equals(const IexTpMessageData& other) const {
    const auto* that = dynamic_cast<const RetailLiquidityIndicatorMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool RetailLiquidityIndicatorMessage::operator==(const RetailLiquidityIndicatorMessage& other) const {
    return retail_liquidity_indicator_ == other.retail_liquidity_indicator_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_;
}

bool RetailLiquidityIndicatorMessage::operator!=(const RetailLiquidityIndicatorMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::tops::snap::v1_6
