#include "PayloadOrderReplaceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

PayloadOrderReplaceMessage::PayloadOrderReplaceMessage(std::chrono::nanoseconds nanoseconds, std::uint64_t original_order_reference_number, std::uint64_t new_order_reference_number, std::uint32_t shares, Decimal price)
  : nanoseconds_(nanoseconds), original_order_reference_number_(original_order_reference_number), new_order_reference_number_(new_order_reference_number), shares_(shares), price_(price) {}

std::chrono::nanoseconds PayloadOrderReplaceMessage::nanoseconds() const { return nanoseconds_; }
void PayloadOrderReplaceMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint64_t PayloadOrderReplaceMessage::original_order_reference_number() const { return original_order_reference_number_; }
void PayloadOrderReplaceMessage::set_original_order_reference_number(std::uint64_t value) { original_order_reference_number_ = value; }

std::uint64_t PayloadOrderReplaceMessage::new_order_reference_number() const { return new_order_reference_number_; }
void PayloadOrderReplaceMessage::set_new_order_reference_number(std::uint64_t value) { new_order_reference_number_ = value; }

std::uint32_t PayloadOrderReplaceMessage::shares() const { return shares_; }
void PayloadOrderReplaceMessage::set_shares(std::uint32_t value) { shares_ = value; }

Decimal PayloadOrderReplaceMessage::price() const { return price_; }
void PayloadOrderReplaceMessage::set_price(Decimal value) { price_ = value; }

PacketMessageCode PayloadOrderReplaceMessage::type() const { return message_type; }

std::string_view PayloadOrderReplaceMessage::name() const { return "Order Replace Message"; }

std::size_t PayloadOrderReplaceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadOrderReplaceMessage", wire_size, length);

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

std::size_t PayloadOrderReplaceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadOrderReplaceMessage", wire_size, capacity);

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

std::size_t PayloadOrderReplaceMessage::encoded_size() const {
    return wire_size;
}

void PayloadOrderReplaceMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadOrderReplaceMessage::clone() const {
    return std::make_unique<PayloadOrderReplaceMessage>(*this);
}

void PayloadOrderReplaceMessage::print(std::ostream& out) const {
    out << "PayloadOrderReplaceMessage{";
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

bool PayloadOrderReplaceMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadOrderReplaceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadOrderReplaceMessage::operator==(const PayloadOrderReplaceMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && original_order_reference_number_ == other.original_order_reference_number_
        && new_order_reference_number_ == other.new_order_reference_number_
        && shares_ == other.shares_
        && price_ == other.price_;
}

bool PayloadOrderReplaceMessage::operator!=(const PayloadOrderReplaceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
