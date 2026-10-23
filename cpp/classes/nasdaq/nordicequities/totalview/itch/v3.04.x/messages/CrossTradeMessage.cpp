#include "CrossTradeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

CrossTradeMessage::CrossTradeMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t quantity, std::uint32_t order_book, Decimal cross_price, std::uint32_t match_number, CrossType cross_type, std::uint32_t number_of_trades)
  : timestamp_(timestamp), tracking_number_(tracking_number), quantity_(quantity), order_book_(order_book), cross_price_(cross_price), match_number_(match_number), cross_type_(cross_type), number_of_trades_(number_of_trades) {}

std::chrono::nanoseconds CrossTradeMessage::timestamp() const { return timestamp_; }
void CrossTradeMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t CrossTradeMessage::tracking_number() const { return tracking_number_; }
void CrossTradeMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint32_t CrossTradeMessage::quantity() const { return quantity_; }
void CrossTradeMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

std::uint32_t CrossTradeMessage::order_book() const { return order_book_; }
void CrossTradeMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

Decimal CrossTradeMessage::cross_price() const { return cross_price_; }
void CrossTradeMessage::set_cross_price(Decimal value) { cross_price_ = value; }

std::uint32_t CrossTradeMessage::match_number() const { return match_number_; }
void CrossTradeMessage::set_match_number(std::uint32_t value) { match_number_ = value; }

CrossType CrossTradeMessage::cross_type() const { return cross_type_; }
void CrossTradeMessage::set_cross_type(CrossType value) { cross_type_ = value; }

std::uint32_t CrossTradeMessage::number_of_trades() const { return number_of_trades_; }
void CrossTradeMessage::set_number_of_trades(std::uint32_t value) { number_of_trades_ = value; }

MessageCode CrossTradeMessage::type() const { return message_type; }

std::string_view CrossTradeMessage::name() const { return "Cross Trade Message"; }

std::size_t CrossTradeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CrossTradeMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    cross_price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    match_number_ = wire::read_u32_be(data + offset);
    offset += 4;

    cross_type_ = static_cast<CrossType>(wire::read_char(data + offset));
    offset += 1;

    number_of_trades_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t CrossTradeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossTradeMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(cross_price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(match_number_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(cross_type_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(number_of_trades_));
    offset += 4;

    return offset;
}

std::size_t CrossTradeMessage::encoded_size() const {
    return wire_size;
}

void CrossTradeMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> CrossTradeMessage::clone() const {
    return std::make_unique<CrossTradeMessage>(*this);
}

void CrossTradeMessage::print(std::ostream& out) const {
    out << "CrossTradeMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", quantity=";
    out << quantity_;
    out << ", order_book=";
    out << order_book_;
    out << ", cross_price=";
    out << cross_price_;
    out << ", match_number=";
    out << match_number_;
    out << ", cross_type=";
    out << cross_type_;
    out << ", number_of_trades=";
    out << number_of_trades_;
    out << '}';
}

bool CrossTradeMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const CrossTradeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CrossTradeMessage::operator==(const CrossTradeMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && quantity_ == other.quantity_
        && order_book_ == other.order_book_
        && cross_price_ == other.cross_price_
        && match_number_ == other.match_number_
        && cross_type_ == other.cross_type_
        && number_of_trades_ == other.number_of_trades_;
}

bool CrossTradeMessage::operator!=(const CrossTradeMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
