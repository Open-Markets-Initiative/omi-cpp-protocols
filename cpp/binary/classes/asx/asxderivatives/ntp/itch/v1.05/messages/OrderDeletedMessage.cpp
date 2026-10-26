#include "OrderDeletedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

OrderDeletedMessage::OrderDeletedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Side side, std::uint64_t order_id)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), side_(side), order_id_(order_id) {}

std::chrono::nanoseconds OrderDeletedMessage::nanoseconds() const { return nanoseconds_; }
void OrderDeletedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t OrderDeletedMessage::trade_date() const { return trade_date_; }
void OrderDeletedMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t OrderDeletedMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void OrderDeletedMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

Side OrderDeletedMessage::side() const { return side_; }
void OrderDeletedMessage::set_side(Side value) { side_ = value; }

std::uint64_t OrderDeletedMessage::order_id() const { return order_id_; }
void OrderDeletedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

MessageCode OrderDeletedMessage::type() const { return message_type; }

std::string_view OrderDeletedMessage::name() const { return "Order Deleted Message"; }

std::size_t OrderDeletedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeletedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    trade_date_ = wire::read_u16_be(data + offset);
    offset += 2;

    tradeable_instrument_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    side_ = static_cast<Side>(wire::read_char(data + offset));
    offset += 1;

    order_id_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderDeletedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeletedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(trade_date_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(tradeable_instrument_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(side_));
    offset += 1;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_id_));
    offset += 8;

    return offset;
}

std::size_t OrderDeletedMessage::encoded_size() const {
    return wire_size;
}

void OrderDeletedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderDeletedMessage::clone() const {
    return std::make_unique<OrderDeletedMessage>(*this);
}

void OrderDeletedMessage::print(std::ostream& out) const {
    out << "OrderDeletedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", trade_date=";
    out << trade_date_;
    out << ", tradeable_instrument_id=";
    out << tradeable_instrument_id_;
    out << ", side=";
    out << side_;
    out << ", order_id=";
    out << order_id_;
    out << '}';
}

bool OrderDeletedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderDeletedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeletedMessage::operator==(const OrderDeletedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && side_ == other.side_
        && order_id_ == other.order_id_;
}

bool OrderDeletedMessage::operator!=(const OrderDeletedMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
