#include "CancelOrderMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

CancelOrderMessage::CancelOrderMessage(std::uint32_t order_token, std::uint32_t quantity)
  : order_token_(order_token), quantity_(quantity) {}

std::uint32_t CancelOrderMessage::order_token() const { return order_token_; }
void CancelOrderMessage::set_order_token(std::uint32_t value) { order_token_ = value; }

std::uint32_t CancelOrderMessage::quantity() const { return quantity_; }
void CancelOrderMessage::set_quantity(std::uint32_t value) { quantity_ = value; }

UnsequencedMessageCode CancelOrderMessage::type() const { return message_type; }

std::string_view CancelOrderMessage::name() const { return "Cancel Order Message"; }

std::size_t CancelOrderMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("CancelOrderMessage", wire_size, length);

    order_token_ = wire::read_u32_be(data + offset);
    offset += 4;

    quantity_ = wire::read_u32_be(data + offset);
    offset += 4;

    return offset;
}

std::size_t CancelOrderMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CancelOrderMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(order_token_));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(quantity_));
    offset += 4;

    return offset;
}

std::size_t CancelOrderMessage::encoded_size() const {
    return wire_size;
}

void CancelOrderMessage::accept(UnsequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<UnsequencedMessage> CancelOrderMessage::clone() const {
    return std::make_unique<CancelOrderMessage>(*this);
}

void CancelOrderMessage::print(std::ostream& out) const {
    out << "CancelOrderMessage{";
    out << "order_token=";
    out << order_token_;
    out << ", quantity=";
    out << quantity_;
    out << '}';
}

bool CancelOrderMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const CancelOrderMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool CancelOrderMessage::operator==(const CancelOrderMessage& other) const {
    return order_token_ == other.order_token_
        && quantity_ == other.quantity_;
}

bool CancelOrderMessage::operator!=(const CancelOrderMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
