#include "PayloadOrderReplaceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadOrderReplaceMessage::PayloadOrderReplaceMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t original_order_reference_number, std::uint64_t new_order_reference_number, std::uint32_t shares, Decimal price)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), original_order_reference_number_(original_order_reference_number), new_order_reference_number_(new_order_reference_number), shares_(shares), price_(price) {}

std::uint16_t PayloadOrderReplaceMessage::stock_locate() const { return stock_locate_; }
void PayloadOrderReplaceMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadOrderReplaceMessage::tracking_number() const { return tracking_number_; }
void PayloadOrderReplaceMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadOrderReplaceMessage::timestamp() const { return timestamp_; }
void PayloadOrderReplaceMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

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

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

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

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

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
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
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
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && original_order_reference_number_ == other.original_order_reference_number_
        && new_order_reference_number_ == other.new_order_reference_number_
        && shares_ == other.shares_
        && price_ == other.price_;
}

bool PayloadOrderReplaceMessage::operator!=(const PayloadOrderReplaceMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
