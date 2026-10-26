#include "OrderBookClearMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

OrderBookClearMessage::OrderBookClearMessage(std::chrono::nanoseconds timestamp, SourceVenue source_venue, std::uint64_t instrument, OrderBookType order_book_type)
  : timestamp_(timestamp), source_venue_(source_venue), instrument_(instrument), order_book_type_(order_book_type) {}

std::chrono::nanoseconds OrderBookClearMessage::timestamp() const { return timestamp_; }
void OrderBookClearMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

SourceVenue OrderBookClearMessage::source_venue() const { return source_venue_; }
void OrderBookClearMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

std::uint64_t OrderBookClearMessage::instrument() const { return instrument_; }
void OrderBookClearMessage::set_instrument(std::uint64_t value) { instrument_ = value; }

OrderBookType OrderBookClearMessage::order_book_type() const { return order_book_type_; }
void OrderBookClearMessage::set_order_book_type(OrderBookType value) { order_book_type_ = value; }

MessageCode OrderBookClearMessage::type() const { return message_type; }

std::string_view OrderBookClearMessage::name() const { return "Order Book Clear Message"; }

std::size_t OrderBookClearMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookClearMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    instrument_ = wire::read_u64_le(data + offset);
    offset += 8;

    order_book_type_ = static_cast<OrderBookType>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t OrderBookClearMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookClearMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(instrument_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(order_book_type_));
    offset += 1;

    return offset;
}

std::size_t OrderBookClearMessage::encoded_size() const {
    return wire_size;
}

void OrderBookClearMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookClearMessage::clone() const {
    return std::make_unique<OrderBookClearMessage>(*this);
}

void OrderBookClearMessage::print(std::ostream& out) const {
    out << "OrderBookClearMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", source_venue=";
    out << source_venue_;
    out << ", instrument=";
    out << instrument_;
    out << ", order_book_type=";
    out << order_book_type_;
    out << '}';
}

bool OrderBookClearMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookClearMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookClearMessage::operator==(const OrderBookClearMessage& other) const {
    return timestamp_ == other.timestamp_
        && source_venue_ == other.source_venue_
        && instrument_ == other.instrument_
        && order_book_type_ == other.order_book_type_;
}

bool OrderBookClearMessage::operator!=(const OrderBookClearMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
