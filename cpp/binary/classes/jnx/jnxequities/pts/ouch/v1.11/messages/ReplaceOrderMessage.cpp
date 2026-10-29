#include "ReplaceOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

ReplaceOrderMessage::ReplaceOrderMessage(std::uint32_t existing_order_token, std::uint32_t replacement_order_token, std::uint32_t quantity, Decimal price, TimeInForce time_in_force, Display display, std::uint32_t minimum_quantity)
  : existing_order_token_(existing_order_token), replacement_order_token_(replacement_order_token), quantity_(quantity), price_(price), time_in_force_(time_in_force), display_(display), minimum_quantity_(minimum_quantity) {}

std::uint32_t ReplaceOrderMessage::existing_order_token() const { return existing_order_token_; }
void ReplaceOrderMessage::set_existing_order_token(std::uint32_t value) { existing_order_token_ = value; }

std::uint32_t ReplaceOrderMessage::replacement_order_token() const { return replacement_order_token_; }
void ReplaceOrderMessage::set_replacement_order_token(std::uint32_t value) { replacement_order_token_ = value; }

std::uint32_t ReplaceOrderMessage::quantity() const { return quantity_; }
void ReplaceOrderMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

Decimal ReplaceOrderMessage::price() const { return price_; }
void ReplaceOrderMessage::set_price(Decimal value) { price_ = value; }

TimeInForce ReplaceOrderMessage::time_in_force() const { return time_in_force_; }
void ReplaceOrderMessage::set_time_in_force(TimeInForce value) { time_in_force_ = value; }

Display ReplaceOrderMessage::display() const { return display_; }
void ReplaceOrderMessage::set_display(Display value) { display_ = value; }

std::uint32_t ReplaceOrderMessage::minimum_quantity() const { return minimum_quantity_; }
void ReplaceOrderMessage::set_minimum_quantity(std::uint32_t value) { minimum_quantity_ = value; }

UnsequencedMessageCode ReplaceOrderMessage::type() const { return message_type; }

std::string_view ReplaceOrderMessage::name() const { return "Replace Order Message"; }

std::size_t ReplaceOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ReplaceOrderMessage", wire_size, length);

    existing_order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    replacement_order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    price_ = Decimal(static_cast<std::int64_t>(wire::read_u32_be(data + offset)), -1);
    offset += 4;

    time_in_force_ = static_cast<TimeInForce>(wire::read_u32_be(data + offset));
    offset += 4;

    display_ = static_cast<Display>(wire::read_char(data + offset));
    offset += 1;

    minimum_quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t ReplaceOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ReplaceOrderMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(existing_order_token_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(replacement_order_token_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(price_.mantissa()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_in_force_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(display_));
    offset += 1;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(minimum_quantity_));
    offset += 4;

    return offset;
}

std::size_t ReplaceOrderMessage::encoded_size() const {
    return wire_size;
}

void ReplaceOrderMessage::accept(UnsequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnsequencedMessage> ReplaceOrderMessage::clone() const {
    return std::make_unique<ReplaceOrderMessage>(*this);
}

void ReplaceOrderMessage::print(std::ostream& out) const {
    out << "ReplaceOrderMessage{";
    out << "existing_order_token=";
    out << existing_order_token_;
    out << ", replacement_order_token=";
    out << replacement_order_token_;
    out << ", quantity=";
    out << quantity_;
    out << ", price=";
    out << price_;
    out << ", time_in_force=";
    out << time_in_force_;
    out << ", display=";
    out << display_;
    out << ", minimum_quantity=";
    out << minimum_quantity_;
    out << '}';
}

bool ReplaceOrderMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const ReplaceOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool ReplaceOrderMessage::operator==(const ReplaceOrderMessage& other) const {
    return existing_order_token_ == other.existing_order_token_
        && replacement_order_token_ == other.replacement_order_token_
        && quantity_ == other.quantity_
        && price_ == other.price_
        && time_in_force_ == other.time_in_force_
        && display_ == other.display_
        && minimum_quantity_ == other.minimum_quantity_;
}

bool ReplaceOrderMessage::operator!=(const ReplaceOrderMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
