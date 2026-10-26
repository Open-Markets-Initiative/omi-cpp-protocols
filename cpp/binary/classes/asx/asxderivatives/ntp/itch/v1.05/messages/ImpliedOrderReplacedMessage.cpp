#include "ImpliedOrderReplacedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

ImpliedOrderReplacedMessage::ImpliedOrderReplacedMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, Side side, std::uint64_t order_id, std::uint64_t order_book_priority, std::uint32_t quantity, Decimal price)
  : nanoseconds_(nanoseconds), trade_date_(trade_date), tradeable_instrument_id_(tradeable_instrument_id), side_(side), order_id_(order_id), order_book_priority_(order_book_priority), quantity_(quantity), price_(price) {}

std::chrono::nanoseconds ImpliedOrderReplacedMessage::nanoseconds() const { return nanoseconds_; }
void ImpliedOrderReplacedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint16_t ImpliedOrderReplacedMessage::trade_date() const { return trade_date_; }
void ImpliedOrderReplacedMessage::set_trade_date(std::uint16_t value) { trade_date_ = value; }

std::uint32_t ImpliedOrderReplacedMessage::tradeable_instrument_id() const { return tradeable_instrument_id_; }
void ImpliedOrderReplacedMessage::set_tradeable_instrument_id(std::uint32_t value) { tradeable_instrument_id_ = value; }

Side ImpliedOrderReplacedMessage::side() const { return side_; }
void ImpliedOrderReplacedMessage::set_side(Side value) { side_ = value; }

std::uint64_t ImpliedOrderReplacedMessage::order_id() const { return order_id_; }
void ImpliedOrderReplacedMessage::set_order_id(std::uint64_t value) { order_id_ = value; }

std::uint64_t ImpliedOrderReplacedMessage::order_book_priority() const { return order_book_priority_; }
void ImpliedOrderReplacedMessage::set_order_book_priority(std::uint64_t value) { order_book_priority_ = value; }

std::uint32_t ImpliedOrderReplacedMessage::quantity() const { return quantity_; }
void ImpliedOrderReplacedMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

Decimal ImpliedOrderReplacedMessage::price() const { return price_; }
void ImpliedOrderReplacedMessage::set_price(Decimal value) { price_ = value; }

MessageCode ImpliedOrderReplacedMessage::type() const { return message_type; }

std::string_view ImpliedOrderReplacedMessage::name() const { return "Implied Order Replaced Message"; }

std::size_t ImpliedOrderReplacedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ImpliedOrderReplacedMessage", wire_size, length);

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

    order_book_priority_ = wire::read_u64_be(data + offset);
    offset += 8;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_i64_be(data + offset)), -2);
    offset += 8;

    return offset;
}

std::size_t ImpliedOrderReplacedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ImpliedOrderReplacedMessage", wire_size, capacity);

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

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_book_priority_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_i64_be(data + offset, static_cast<std::int64_t>(price_.mantissa()));
    offset += 8;

    return offset;
}

std::size_t ImpliedOrderReplacedMessage::encoded_size() const {
    return wire_size;
}

void ImpliedOrderReplacedMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> ImpliedOrderReplacedMessage::clone() const {
    return std::make_unique<ImpliedOrderReplacedMessage>(*this);
}

void ImpliedOrderReplacedMessage::print(std::ostream& out) const {
    out << "ImpliedOrderReplacedMessage{";
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
    out << ", order_book_priority=";
    out << order_book_priority_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool ImpliedOrderReplacedMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const ImpliedOrderReplacedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ImpliedOrderReplacedMessage::operator==(const ImpliedOrderReplacedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && trade_date_ == other.trade_date_
        && tradeable_instrument_id_ == other.tradeable_instrument_id_
        && side_ == other.side_
        && order_id_ == other.order_id_
        && order_book_priority_ == other.order_book_priority_
        && quantity_ == other.quantity_
        && price_ == other.price_;
}

bool ImpliedOrderReplacedMessage::operator!=(const ImpliedOrderReplacedMessage& other) const {
    return !(*this == other);
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
