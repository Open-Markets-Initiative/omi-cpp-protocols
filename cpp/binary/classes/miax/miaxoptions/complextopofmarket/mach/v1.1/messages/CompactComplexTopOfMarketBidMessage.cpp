#include "CompactComplexTopOfMarketBidMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

CompactComplexTopOfMarketBidMessage::CompactComplexTopOfMarketBidMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t strategy_id, Decimal compact_price, std::uint16_t compact_size, TopOfMarketQuoteCondition top_of_market_quote_condition)
  : nanoseconds_(nanoseconds), strategy_id_(strategy_id), compact_price_(compact_price), compact_size_(compact_size), top_of_market_quote_condition_(top_of_market_quote_condition) {}

std::chrono::nanoseconds CompactComplexTopOfMarketBidMessage::nanoseconds() const { return nanoseconds_; }
void CompactComplexTopOfMarketBidMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t CompactComplexTopOfMarketBidMessage::strategy_id() const { return strategy_id_; }
void CompactComplexTopOfMarketBidMessage::set_strategy_id(std::uint32_t value) { strategy_id_ = value; }

Decimal CompactComplexTopOfMarketBidMessage::compact_price() const { return compact_price_; }
void CompactComplexTopOfMarketBidMessage::set_compact_price(Decimal value) { compact_price_ = value; }

std::uint16_t CompactComplexTopOfMarketBidMessage::compact_size() const { return compact_size_; }
void CompactComplexTopOfMarketBidMessage::set_compact_size(std::uint16_t value) { compact_size_ = value; }

TopOfMarketQuoteCondition CompactComplexTopOfMarketBidMessage::top_of_market_quote_condition() const { return top_of_market_quote_condition_; }
void CompactComplexTopOfMarketBidMessage::set_top_of_market_quote_condition(TopOfMarketQuoteCondition value) { top_of_market_quote_condition_ = value; }

DataCode CompactComplexTopOfMarketBidMessage::type() const { return message_type; }

std::string_view CompactComplexTopOfMarketBidMessage::name() const { return "Compact Complex Top Of Market Bid Message"; }

std::size_t CompactComplexTopOfMarketBidMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CompactComplexTopOfMarketBidMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    strategy_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    compact_price_ = Decimal(static_cast<std::int64_t>(wire::read_i16_le(data + offset)), -2);
    offset += 2;

    compact_size_ = wire::read_u16_le(data + offset);
    offset += 2;

    top_of_market_quote_condition_ = static_cast<TopOfMarketQuoteCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t CompactComplexTopOfMarketBidMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CompactComplexTopOfMarketBidMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(strategy_id_));
    offset += 4;

    wire::write_i16_le(data + offset, static_cast<std::int16_t>(compact_price_.mantissa()));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(compact_size_));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(top_of_market_quote_condition_));
    offset += 1;

    return offset;
}

std::size_t CompactComplexTopOfMarketBidMessage::encoded_size() const {
    return wire_size;
}

void CompactComplexTopOfMarketBidMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> CompactComplexTopOfMarketBidMessage::clone() const {
    return std::make_unique<CompactComplexTopOfMarketBidMessage>(*this);
}

void CompactComplexTopOfMarketBidMessage::print(std::ostream& out) const {
    out << "CompactComplexTopOfMarketBidMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", strategy_id=";
    out << strategy_id_;
    out << ", compact_price=";
    out << compact_price_;
    out << ", compact_size=";
    out << compact_size_;
    out << ", top_of_market_quote_condition=";
    out << top_of_market_quote_condition_;
    out << '}';
}

bool CompactComplexTopOfMarketBidMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const CompactComplexTopOfMarketBidMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CompactComplexTopOfMarketBidMessage::operator==(const CompactComplexTopOfMarketBidMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && strategy_id_ == other.strategy_id_
        && compact_price_ == other.compact_price_
        && compact_size_ == other.compact_size_
        && top_of_market_quote_condition_ == other.top_of_market_quote_condition_;
}

bool CompactComplexTopOfMarketBidMessage::operator!=(const CompactComplexTopOfMarketBidMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
