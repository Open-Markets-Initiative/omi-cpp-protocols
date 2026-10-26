#include "OrderBookFlushMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

OrderBookFlushMessage::OrderBookFlushMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t order_book)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_book_(order_book) {}

std::chrono::nanoseconds OrderBookFlushMessage::timestamp() const { return timestamp_; }
void OrderBookFlushMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t OrderBookFlushMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "UTC").utc(static_cast<std::int64_t>(timestamp_.count())); }

std::uint16_t OrderBookFlushMessage::tracking_number() const { return tracking_number_; }
void OrderBookFlushMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint32_t OrderBookFlushMessage::order_book() const { return order_book_; }
void OrderBookFlushMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

MessageCode OrderBookFlushMessage::type() const { return message_type; }

std::string_view OrderBookFlushMessage::name() const { return "Order Book Flush Message"; }

std::size_t OrderBookFlushMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookFlushMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t OrderBookFlushMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookFlushMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    return offset;
}

std::size_t OrderBookFlushMessage::encoded_size() const {
    return wire_size;
}

void OrderBookFlushMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookFlushMessage::clone() const {
    return std::make_unique<OrderBookFlushMessage>(*this);
}

void OrderBookFlushMessage::print(std::ostream& out) const {
    out << "OrderBookFlushMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "UTC");
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_book=";
    out << order_book_;
    out << '}';
}

bool OrderBookFlushMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookFlushMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookFlushMessage::operator==(const OrderBookFlushMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_book_ == other.order_book_;
}

bool OrderBookFlushMessage::operator!=(const OrderBookFlushMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
