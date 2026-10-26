#include "OrderBookClearMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

OrderBookClearMessage::OrderBookClearMessage(std::uint32_t nanosecond, std::uint32_t instrument_id, const std::array<std::byte, 1>& reserved_a, const std::array<std::byte, 1>& reserved_b, const OrderBookClearFlags& order_book_clear_flags)
  : nanosecond_(nanosecond), instrument_id_(instrument_id), reserved_a_(reserved_a), reserved_b_(reserved_b), order_book_clear_flags_(order_book_clear_flags) {}

std::uint32_t OrderBookClearMessage::nanosecond() const { return nanosecond_; }
void OrderBookClearMessage::set_nanosecond(std::uint32_t value) { nanosecond_ = value; }

std::uint32_t OrderBookClearMessage::instrument_id() const { return instrument_id_; }
void OrderBookClearMessage::set_instrument_id(std::uint32_t value) { instrument_id_ = value; }

const std::array<std::byte, 1>& OrderBookClearMessage::reserved_a() const { return reserved_a_; }
std::array<std::byte, 1>& OrderBookClearMessage::reserved_a() { return reserved_a_; }
void OrderBookClearMessage::set_reserved_a(const std::array<std::byte, 1>& value) { reserved_a_ = value; }

const std::array<std::byte, 1>& OrderBookClearMessage::reserved_b() const { return reserved_b_; }
std::array<std::byte, 1>& OrderBookClearMessage::reserved_b() { return reserved_b_; }
void OrderBookClearMessage::set_reserved_b(const std::array<std::byte, 1>& value) { reserved_b_ = value; }

const OrderBookClearFlags& OrderBookClearMessage::order_book_clear_flags() const { return order_book_clear_flags_; }
OrderBookClearFlags& OrderBookClearMessage::order_book_clear_flags() { return order_book_clear_flags_; }
void OrderBookClearMessage::set_order_book_clear_flags(const OrderBookClearFlags& value) { order_book_clear_flags_ = value; }

MessageCode OrderBookClearMessage::type() const { return message_type; }

std::string_view OrderBookClearMessage::name() const { return "Order Book Clear Message"; }

std::size_t OrderBookClearMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderBookClearMessage", wire_size, length);

    nanosecond_ = wire::read_u32_le(data + offset);
    offset += 4;

    instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::read_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    offset += order_book_clear_flags_.decode(data + offset, length - offset);

    return offset;
}

std::size_t OrderBookClearMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderBookClearMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanosecond_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(instrument_id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_a_.data(), 1);
    offset += 1;

    wire::write_bytes(data + offset, reserved_b_.data(), 1);
    offset += 1;

    offset += order_book_clear_flags_.encode(data + offset, capacity - offset);

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
    out << "nanosecond=";
    out << nanosecond_;
    out << ", instrument_id=";
    out << instrument_id_;
    out << ", reserved_a=";
    print::hex(out, reserved_a_.data(), reserved_a_.size());
    out << ", reserved_b=";
    print::hex(out, reserved_b_.data(), reserved_b_.size());
    out << ", order_book_clear_flags=";
    order_book_clear_flags_.print(out);
    out << '}';
}

bool OrderBookClearMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const OrderBookClearMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderBookClearMessage::operator==(const OrderBookClearMessage& other) const {
    return nanosecond_ == other.nanosecond_
        && instrument_id_ == other.instrument_id_
        && reserved_a_ == other.reserved_a_
        && reserved_b_ == other.reserved_b_
        && order_book_clear_flags_ == other.order_book_clear_flags_;
}

bool OrderBookClearMessage::operator!=(const OrderBookClearMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::millennium::level2::mitch::v11_9
