#include "OrderReplaceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

OrderReplaceMessage::OrderReplaceMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t original_order_reference_number, std::uint64_t new_order_reference_number, std::uint32_t shares, Decimal price)
  : nanoseconds_(nanoseconds), original_order_reference_number_(original_order_reference_number), new_order_reference_number_(new_order_reference_number), shares_(shares), price_(price) {}

std::chrono::nanoseconds OrderReplaceMessage::nanoseconds() const { return nanoseconds_; }
void OrderReplaceMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t OrderReplaceMessage::original_order_reference_number() const { return original_order_reference_number_; }
void OrderReplaceMessage::set_original_order_reference_number(std::uint64_t value) { original_order_reference_number_ = value; }

std::uint64_t OrderReplaceMessage::new_order_reference_number() const { return new_order_reference_number_; }
void OrderReplaceMessage::set_new_order_reference_number(std::uint64_t value) { new_order_reference_number_ = value; }

std::uint32_t OrderReplaceMessage::shares() const { return shares_; }
void OrderReplaceMessage::set_shares(std::uint32_t value) { shares_ = value; }

Decimal OrderReplaceMessage::price() const { return price_; }
void OrderReplaceMessage::set_price(Decimal value) { price_ = value; }

SequencedMessageCode OrderReplaceMessage::type() const { return message_type; }

std::string_view OrderReplaceMessage::name() const { return "Order Replace Message"; }

std::size_t OrderReplaceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("OrderReplaceMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    original_order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    new_order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    shares_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -4);
    offset += 4;

    return offset;
}

std::size_t OrderReplaceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OrderReplaceMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(original_order_reference_number_));
    offset += 8;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(new_order_reference_number_));
    offset += 8;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(shares_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    return offset;
}

std::size_t OrderReplaceMessage::encoded_size() const {
    return wire_size;
}

void OrderReplaceMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> OrderReplaceMessage::clone() const {
    return std::make_unique<OrderReplaceMessage>(*this);
}

void OrderReplaceMessage::print(std::ostream& out) const {
    out << "OrderReplaceMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", original_order_reference_number=";
    out << original_order_reference_number_;
    out << ", new_order_reference_number=";
    out << new_order_reference_number_;
    out << ", shares=";
    out << shares_;
    out << ", price=";
    out << price_;
    out << '}';
}

bool OrderReplaceMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const OrderReplaceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool OrderReplaceMessage::operator==(const OrderReplaceMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && original_order_reference_number_ == other.original_order_reference_number_
        && new_order_reference_number_ == other.new_order_reference_number_
        && shares_ == other.shares_
        && price_ == other.price_;
}

bool OrderReplaceMessage::operator!=(const OrderReplaceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
