#include "OrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

OrderDeleteMessage::OrderDeleteMessage(char reserved_1, std::chrono::nanoseconds timestamp, const std::string& symbol, std::uint64_t order_id_reference)
  : reserved_1_(reserved_1), timestamp_(timestamp), symbol_(symbol), order_id_reference_(order_id_reference) {}

char OrderDeleteMessage::reserved_1() const { return reserved_1_; }
void OrderDeleteMessage::set_reserved_1(char value) { reserved_1_ = value; }

std::chrono::nanoseconds OrderDeleteMessage::timestamp() const { return timestamp_; }
void OrderDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

const std::string& OrderDeleteMessage::symbol() const { return symbol_; }
std::string& OrderDeleteMessage::symbol() { return symbol_; }
void OrderDeleteMessage::set_symbol(const std::string& value) { symbol_ = value; }

std::uint64_t OrderDeleteMessage::order_id_reference() const { return order_id_reference_; }
void OrderDeleteMessage::set_order_id_reference(std::uint64_t value) { order_id_reference_ = value; }

MessageCode OrderDeleteMessage::type() const { return message_type; }

std::string_view OrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t OrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderDeleteMessage", wire_size, length);

    reserved_1_ = wire::read_char(data + offset);
    offset += 1;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_i64_le(data + offset)));
    offset += 8;

    symbol_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    order_id_reference_ = wire::read_u64_le(data + offset);
    offset += 8;

    return offset;
}

std::size_t OrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderDeleteMessage", wire_size, capacity);

    wire::write_char(data + offset, reserved_1_);
    offset += 1;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 8, ' ', symbol_);
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(order_id_reference_));
    offset += 8;

    return offset;
}

std::size_t OrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void OrderDeleteMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> OrderDeleteMessage::clone() const {
    return std::make_unique<OrderDeleteMessage>(*this);
}

void OrderDeleteMessage::print(std::ostream& out) const {
    out << "OrderDeleteMessage{";
    out << "reserved_1=";
    print::character(out, reserved_1_);
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", order_id_reference=";
    out << order_id_reference_;
    out << '}';
}

bool OrderDeleteMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderDeleteMessage::operator==(const OrderDeleteMessage& other) const {
    return reserved_1_ == other.reserved_1_
        && timestamp_ == other.timestamp_
        && symbol_ == other.symbol_
        && order_id_reference_ == other.order_id_reference_;
}

bool OrderDeleteMessage::operator!=(const OrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace iex::iexequities::deepplus::iextp::v1_04
