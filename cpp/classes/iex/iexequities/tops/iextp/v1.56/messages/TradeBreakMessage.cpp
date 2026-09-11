#include "TradeBreakMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

TradeBreakMessage::TradeBreakMessage(const SaleConditionFlags& sale_condition_flags, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint32_t size, Decimal price, std::uint64_t trade_id)
  : sale_condition_flags_(sale_condition_flags), timestamp_(timestamp), symbol_(symbol), size_(size), price_(price), trade_id_(trade_id) {}

const SaleConditionFlags& TradeBreakMessage::sale_condition_flags() const { return sale_condition_flags_; }
SaleConditionFlags& TradeBreakMessage::sale_condition_flags() { return sale_condition_flags_; }
void TradeBreakMessage::set_sale_condition_flags(const SaleConditionFlags& value) { sale_condition_flags_ = value; }

std::chrono::nanoseconds TradeBreakMessage::timestamp() const { return timestamp_; }
void TradeBreakMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& TradeBreakMessage::symbol() const { return symbol_; }
std::string& TradeBreakMessage::symbol() { return symbol_; }
void TradeBreakMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint32_t TradeBreakMessage::size() const { return size_; }
void TradeBreakMessage::set_size(std::uint32_t value) { size_ = value; }

Decimal TradeBreakMessage::price() const { return price_; }
void TradeBreakMessage::set_price(Decimal value) { price_ = value; }

std::uint64_t TradeBreakMessage::trade_id() const { return trade_id_; }
void TradeBreakMessage::set_trade_id(std::uint64_t value) { trade_id_ = value; }

MessageCode TradeBreakMessage::type() const { return message_type; }

std::string_view TradeBreakMessage::name() const { return "Trade Break Message"; }

std::size_t TradeBreakMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeBreakMessage", wire_size, length);

    offset += sale_condition_flags_.decode(data + offset, length - offset);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    size_ = wire::read_u32_le(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -4);
    offset += 8;

    trade_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t TradeBreakMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeBreakMessage", wire_size, capacity);

    offset += sale_condition_flags_.encode(data + offset, capacity - offset);

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(size_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(trade_id_));
    offset += 8;

    return offset;
}

std::size_t TradeBreakMessage::encoded_size() const {
    return wire_size;
}

void TradeBreakMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeBreakMessage::clone() const {
    return std::make_unique<TradeBreakMessage>(*this);
}

void TradeBreakMessage::print(std::ostream& out) const {
    out << "TradeBreakMessage{";
    out << "sale_condition_flags=";
    sale_condition_flags_.print(out);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", size=";
    out << size_;
    out << ", price=";
    out << price_;
    out << ", trade_id=";
    out << trade_id_;
    out << '}';
}

bool TradeBreakMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeBreakMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeBreakMessage::operator==(const TradeBreakMessage& other) const {
    return sale_condition_flags_ == other.sale_condition_flags_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && size_ == other.size_
        && price_ == other.price_
        && trade_id_ == other.trade_id_;
}

bool TradeBreakMessage::operator!=(const TradeBreakMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::tops::iextp::v1_56
