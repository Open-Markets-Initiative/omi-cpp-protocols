// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/OrderBookTermsMessage.cpp
#include "OrderBookTermsMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

OrderBookTermsMessage::OrderBookTermsMessage(const std::string& symbol, std::optional<std::uint16_t> broker_number, OrderSide order_side, std::optional<std::uint64_t> order_id, std::optional<Decimal> price, std::optional<std::uint32_t> volume, NonResident non_resident, SettlementTerms settlement_terms, std::optional<std::uint32_t> settlement_date, std::optional<std::chrono::microseconds> priority_time_stamp)
  : symbol_(symbol), broker_number_(broker_number), order_side_(order_side), order_id_(order_id), price_(price), volume_(volume), non_resident_(non_resident), settlement_terms_(settlement_terms), settlement_date_(settlement_date), priority_time_stamp_(priority_time_stamp) {}

const std::string& OrderBookTermsMessage::symbol() const { return symbol_; }
std::string& OrderBookTermsMessage::symbol() { return symbol_; }
void OrderBookTermsMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::optional<std::uint16_t> OrderBookTermsMessage::broker_number() const { return broker_number_; }
void OrderBookTermsMessage::set_broker_number(std::optional<std::uint16_t> value) { broker_number_ = value; }

OrderSide OrderBookTermsMessage::order_side() const { return order_side_; }
void OrderBookTermsMessage::set_order_side(OrderSide value) { order_side_ = value; }

std::optional<std::uint64_t> OrderBookTermsMessage::order_id() const { return order_id_; }
void OrderBookTermsMessage::set_order_id(std::optional<std::uint64_t> value) { order_id_ = value; }

std::optional<Decimal> OrderBookTermsMessage::price() const { return price_; }
void OrderBookTermsMessage::set_price(std::optional<Decimal> value) { price_ = value; }

std::optional<std::uint32_t> OrderBookTermsMessage::volume() const { return volume_; }
void OrderBookTermsMessage::set_volume(std::optional<std::uint32_t> value) { volume_ = value; }

NonResident OrderBookTermsMessage::non_resident() const { return non_resident_; }
void OrderBookTermsMessage::set_non_resident(NonResident value) { non_resident_ = value; }

SettlementTerms OrderBookTermsMessage::settlement_terms() const { return settlement_terms_; }
void OrderBookTermsMessage::set_settlement_terms(SettlementTerms value) { settlement_terms_ = value; }

std::optional<std::uint32_t> OrderBookTermsMessage::settlement_date() const { return settlement_date_; }
void OrderBookTermsMessage::set_settlement_date(std::optional<std::uint32_t> value) { settlement_date_ = value; }

std::optional<std::chrono::microseconds> OrderBookTermsMessage::priority_time_stamp() const { return priority_time_stamp_; }
void OrderBookTermsMessage::set_priority_time_stamp(std::optional<std::chrono::microseconds> value) { priority_time_stamp_ = value; }

MessageCode OrderBookTermsMessage::type() const { return message_type; }

std::string_view OrderBookTermsMessage::name() const { return "Order Book Terms Message"; }

std::size_t OrderBookTermsMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookTermsMessage", wire_size, length);

    symbol_ = wire::read_text(data + offset, 9, ' ');
    offset += 9;

    broker_number_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(0ULL));
    offset += 2;

    order_side_ = static_cast<OrderSide>(wire::read_char(data + offset));
    offset += 1;

    order_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    price_ = wire::nullable_decimal(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL), -6);
    offset += 8;

    volume_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    non_resident_ = static_cast<NonResident>(wire::read_char(data + offset));
    offset += 1;

    settlement_terms_ = static_cast<SettlementTerms>(wire::read_char(data + offset));
    offset += 1;

    settlement_date_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    priority_time_stamp_ = wire::nullable_duration<std::chrono::microseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderBookTermsMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookTermsMessage", wire_size, capacity);

    wire::write_text(data + offset, 9, ' ', symbol_);
    offset += 9;

    wire::write_u16_le(data + offset, broker_number_.value_or(static_cast<std::uint16_t>(0ULL)));
    offset += 2;

    wire::write_char(data + offset, static_cast<char>(order_side_));
    offset += 1;

    wire::write_u64_le(data + offset, order_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, price_ ? static_cast<std::uint64_t>(price_->mantissa()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::write_u32_le(data + offset, volume_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(non_resident_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(settlement_terms_));
    offset += 1;

    wire::write_u32_le(data + offset, settlement_date_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_u64_le(data + offset, priority_time_stamp_ ? static_cast<std::uint64_t>(priority_time_stamp_->count()) : static_cast<std::uint64_t>(0ULL));
    offset += 8;

    return offset;
}

std::size_t OrderBookTermsMessage::encoded_size() const {
    return wire_size;
}

void OrderBookTermsMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookTermsMessage::clone() const {
    return std::make_unique<OrderBookTermsMessage>(*this);
}

void OrderBookTermsMessage::print(std::ostream& out) const {
    out << "OrderBookTermsMessage{";
    out << "symbol=";
    print::text(out, symbol_);
    out << ", broker_number=";
    print::optional(out, broker_number_);
    out << ", order_side=";
    out << order_side_;
    out << ", order_id=";
    print::optional(out, order_id_);
    out << ", price=";
    print::optional(out, price_);
    out << ", volume=";
    print::optional(out, volume_);
    out << ", non_resident=";
    out << non_resident_;
    out << ", settlement_terms=";
    out << settlement_terms_;
    out << ", settlement_date=";
    print::optional(out, settlement_date_);
    out << ", priority_time_stamp=";
    print::optional_duration(out, priority_time_stamp_);
    out << '}';
}

bool OrderBookTermsMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookTermsMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookTermsMessage::operator==(const OrderBookTermsMessage& other) const {
    return symbol_ == other.symbol_
        && broker_number_ == other.broker_number_
        && order_side_ == other.order_side_
        && order_id_ == other.order_id_
        && price_ == other.price_
        && volume_ == other.volume_
        && non_resident_ == other.non_resident_
        && settlement_terms_ == other.settlement_terms_
        && settlement_date_ == other.settlement_date_
        && priority_time_stamp_ == other.priority_time_stamp_;
}

bool OrderBookTermsMessage::operator!=(const OrderBookTermsMessage& other) const {
    return !(*this == other);
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
