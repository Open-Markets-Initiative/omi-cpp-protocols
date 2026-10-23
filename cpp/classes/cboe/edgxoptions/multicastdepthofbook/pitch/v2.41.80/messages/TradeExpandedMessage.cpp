#include "TradeExpandedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

TradeExpandedMessage::TradeExpandedMessage(std::chrono::nanoseconds time_offset, std::uint64_t order_id, SideIndicator side_indicator, std::uint32_t quantity_long, const std::string& expanded_symbol, Decimal price_long, std::uint64_t execution_id, TradeCondition trade_condition)
  : time_offset_(time_offset), order_id_(order_id), side_indicator_(side_indicator), quantity_long_(quantity_long), expanded_symbol_(expanded_symbol), price_long_(price_long), execution_id_(execution_id), trade_condition_(trade_condition) {}

std::chrono::nanoseconds TradeExpandedMessage::time_offset() const { return time_offset_; }
void TradeExpandedMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

std::uint64_t TradeExpandedMessage::order_id() const { return order_id_; }
void TradeExpandedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

SideIndicator TradeExpandedMessage::side_indicator() const { return side_indicator_; }
void TradeExpandedMessage::set_side_indicator(SideIndicator value) { side_indicator_ = value; }

std::uint32_t TradeExpandedMessage::quantity_long() const { return quantity_long_; }
void TradeExpandedMessage::set_quantity_long(std::uint32_t value) { quantity_long_ = value; }

const std::string& TradeExpandedMessage::expanded_symbol() const { return expanded_symbol_; }
std::string& TradeExpandedMessage::expanded_symbol() { return expanded_symbol_; }
void TradeExpandedMessage::set_expanded_symbol(const std::string& value) { expanded_symbol_ = value; }

Decimal TradeExpandedMessage::price_long() const { return price_long_; }
void TradeExpandedMessage::set_price_long(Decimal value) { price_long_ = value; }

std::uint64_t TradeExpandedMessage::execution_id() const { return execution_id_; }
void TradeExpandedMessage::set_execution_id(std::uint64_t value) { execution_id_ = value; }

TradeCondition TradeExpandedMessage::trade_condition() const { return trade_condition_; }
void TradeExpandedMessage::set_trade_condition(TradeCondition value) { trade_condition_ = value; }

MessageCode TradeExpandedMessage::type() const { return message_type; }

std::string_view TradeExpandedMessage::name() const { return "Trade Expanded Message"; }

std::size_t TradeExpandedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TradeExpandedMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    order_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    side_indicator_ = static_cast<SideIndicator>(wire::read_char(data + offset));
    offset += 1;

    quantity_long_ = wire::read_u32_le(data + offset);
    offset += 4;

    expanded_symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    price_long_ = Decimal(static_cast<std::int64_t>(wire::read_u64_le(data + offset)), -4);
    offset += 8;

    execution_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    trade_condition_ = static_cast<TradeCondition>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t TradeExpandedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradeExpandedMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(side_indicator_));
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(quantity_long_));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', expanded_symbol_);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(price_long_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(execution_id_));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(trade_condition_));
    offset += 1;

    return offset;
}

std::size_t TradeExpandedMessage::encoded_size() const {
    return wire_size;
}

void TradeExpandedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TradeExpandedMessage::clone() const {
    return std::make_unique<TradeExpandedMessage>(*this);
}

void TradeExpandedMessage::print(std::ostream& out) const {
    out << "TradeExpandedMessage{";
    out << "time_offset=";
    out << time_offset_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side_indicator=";
    out << side_indicator_;
    out << ", quantity_long=";
    out << quantity_long_;
    out << ", expanded_symbol=";
    print::text(out, expanded_symbol_);
    out << ", price_long=";
    out << price_long_;
    out << ", execution_id=";
    out << execution_id_;
    out << ", trade_condition=";
    out << trade_condition_;
    out << '}';
}

bool TradeExpandedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TradeExpandedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TradeExpandedMessage::operator==(const TradeExpandedMessage& other) const {
    return time_offset_ == other.time_offset_
        && order_id_ == other.order_id_
        && side_indicator_ == other.side_indicator_
        && quantity_long_ == other.quantity_long_
        && expanded_symbol_ == other.expanded_symbol_
        && price_long_ == other.price_long_
        && execution_id_ == other.execution_id_
        && trade_condition_ == other.trade_condition_;
}

bool TradeExpandedMessage::operator!=(const TradeExpandedMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
