#include "OrderBookTradingActionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

OrderBookTradingActionMessage::OrderBookTradingActionMessage(std::chrono::nanoseconds timestamp, std::uint16_t tracking_number, std::uint32_t order_book, SymbolState symbol_state, Extension extension, const std::string& reason)
  : timestamp_(timestamp), tracking_number_(tracking_number), order_book_(order_book), symbol_state_(symbol_state), extension_(extension), reason_(reason) {}

std::chrono::nanoseconds OrderBookTradingActionMessage::timestamp() const { return timestamp_; }
void OrderBookTradingActionMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint16_t OrderBookTradingActionMessage::tracking_number() const { return tracking_number_; }
void OrderBookTradingActionMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::uint32_t OrderBookTradingActionMessage::order_book() const { return order_book_; }
void OrderBookTradingActionMessage::set_order_book(std::uint32_t value) { order_book_ = value; }

SymbolState OrderBookTradingActionMessage::symbol_state() const { return symbol_state_; }
void OrderBookTradingActionMessage::set_symbol_state(SymbolState value) { symbol_state_ = value; }

Extension OrderBookTradingActionMessage::extension() const { return extension_; }
void OrderBookTradingActionMessage::set_extension(Extension value) { extension_ = value; }

const std::string& OrderBookTradingActionMessage::reason() const { return reason_; }
std::string& OrderBookTradingActionMessage::reason() { return reason_; }
void OrderBookTradingActionMessage::set_reason(const std::string& value) { reason_ = value; }

MessageCode OrderBookTradingActionMessage::type() const { return message_type; }

std::string_view OrderBookTradingActionMessage::name() const { return "Order Book Trading Action Message"; }

std::size_t OrderBookTradingActionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookTradingActionMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    order_book_ = wire::read_u32_be(data + offset);
    offset += 4;

    symbol_state_ = static_cast<SymbolState>(wire::read_char(data + offset));
    offset += 1;

    extension_ = static_cast<Extension>(wire::read_char(data + offset));
    offset += 1;

    reason_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    return offset;
}

std::size_t OrderBookTradingActionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookTradingActionMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_book_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(symbol_state_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(extension_));
    offset += 1;

    wire::write_text(data + offset, 4, ' ', reason_);
    offset += 4;

    return offset;
}

std::size_t OrderBookTradingActionMessage::encoded_size() const {
    return wire_size;
}

void OrderBookTradingActionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderBookTradingActionMessage::clone() const {
    return std::make_unique<OrderBookTradingActionMessage>(*this);
}

void OrderBookTradingActionMessage::print(std::ostream& out) const {
    out << "OrderBookTradingActionMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", order_book=";
    out << order_book_;
    out << ", symbol_state=";
    out << symbol_state_;
    out << ", extension=";
    out << extension_;
    out << ", reason=";
    print::text(out, reason_);
    out << '}';
}

bool OrderBookTradingActionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookTradingActionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookTradingActionMessage::operator==(const OrderBookTradingActionMessage& other) const {
    return timestamp_ == other.timestamp_
        && tracking_number_ == other.tracking_number_
        && order_book_ == other.order_book_
        && symbol_state_ == other.symbol_state_
        && extension_ == other.extension_
        && reason_ == other.reason_;
}

bool OrderBookTradingActionMessage::operator!=(const OrderBookTradingActionMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
