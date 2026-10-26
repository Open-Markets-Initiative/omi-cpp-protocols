#include "OrderExecutedWithPriceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

OrderExecutedWithPriceMessage::OrderExecutedWithPriceMessage(std::chrono::microseconds time_microseconds, std::uint32_t order_id, Side side, std::uint64_t volume, std::uint32_t match_id, Decimal execution_price, AdoptedPricingMethod adopted_pricing_method)
  : time_microseconds_(time_microseconds), order_id_(order_id), side_(side), volume_(volume), match_id_(match_id), execution_price_(execution_price), adopted_pricing_method_(adopted_pricing_method) {}

std::chrono::microseconds OrderExecutedWithPriceMessage::time_microseconds() const { return time_microseconds_; }
void OrderExecutedWithPriceMessage::set_time_microseconds(std::chrono::microseconds value) { time_microseconds_ = value; }

std::uint32_t OrderExecutedWithPriceMessage::order_id() const { return order_id_; }
void OrderExecutedWithPriceMessage::set_order_id(std::uint32_t value) { order_id_ = value; }

Side OrderExecutedWithPriceMessage::side() const { return side_; }
void OrderExecutedWithPriceMessage::set_side(Side value) { side_ = value; }

std::uint64_t OrderExecutedWithPriceMessage::volume() const { return volume_; }
void OrderExecutedWithPriceMessage::set_volume(std::uint64_t value) { volume_ = value; }

std::uint32_t OrderExecutedWithPriceMessage::match_id() const { return match_id_; }
void OrderExecutedWithPriceMessage::set_match_id(std::uint32_t value) { match_id_ = value; }

Decimal OrderExecutedWithPriceMessage::execution_price() const { return execution_price_; }
void OrderExecutedWithPriceMessage::set_execution_price(Decimal value) { execution_price_ = value; }

AdoptedPricingMethod OrderExecutedWithPriceMessage::adopted_pricing_method() const { return adopted_pricing_method_; }
void OrderExecutedWithPriceMessage::set_adopted_pricing_method(AdoptedPricingMethod value) { adopted_pricing_method_ = value; }

MessageCode OrderExecutedWithPriceMessage::type() const { return message_type; }

std::string_view OrderExecutedWithPriceMessage::name() const { return "Order Executed With Price Message"; }

std::size_t OrderExecutedWithPriceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderExecutedWithPriceMessage", wire_size, length);

    time_microseconds_ = std::chrono::microseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    order_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    volume_ = wire::read_u48_be(data + offset);
    offset += 6;

    match_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    execution_price_ = Decimal(static_cast<std::int64_t>(wire::read_u64_be(data + offset)), -4);
    offset += 8;

    adopted_pricing_method_ = static_cast<AdoptedPricingMethod>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderExecutedWithPriceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderExecutedWithPriceMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_microseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(volume_));
    offset += 6;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_id_));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(execution_price_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(adopted_pricing_method_));
    offset += 1;

    return offset;
}

std::size_t OrderExecutedWithPriceMessage::encoded_size() const {
    return wire_size;
}

void OrderExecutedWithPriceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderExecutedWithPriceMessage::clone() const {
    return std::make_unique<OrderExecutedWithPriceMessage>(*this);
}

void OrderExecutedWithPriceMessage::print(std::ostream& out) const {
    out << "OrderExecutedWithPriceMessage{";
    out << "time_microseconds=";
    out << time_microseconds_.count();
    out << ", order_id=";
    out << order_id_;
    out << ", side=";
    out << side_;
    out << ", volume=";
    out << volume_;
    out << ", match_id=";
    out << match_id_;
    out << ", execution_price=";
    out << execution_price_;
    out << ", adopted_pricing_method=";
    out << adopted_pricing_method_;
    out << '}';
}

bool OrderExecutedWithPriceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderExecutedWithPriceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderExecutedWithPriceMessage::operator==(const OrderExecutedWithPriceMessage& other) const {
    return time_microseconds_ == other.time_microseconds_
        && order_id_ == other.order_id_
        && side_ == other.side_
        && volume_ == other.volume_
        && match_id_ == other.match_id_
        && execution_price_ == other.execution_price_
        && adopted_pricing_method_ == other.adopted_pricing_method_;
}

bool OrderExecutedWithPriceMessage::operator!=(const OrderExecutedWithPriceMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
