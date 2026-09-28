#include "PayloadOrderDeleteMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

PayloadOrderDeleteMessage::PayloadOrderDeleteMessage(std::uint16_t stock_locate, std::uint16_t tracking_number, std::chrono::nanoseconds timestamp, std::uint64_t order_reference_number)
  : stock_locate_(stock_locate), tracking_number_(tracking_number), timestamp_(timestamp), order_reference_number_(order_reference_number) {}

std::uint16_t PayloadOrderDeleteMessage::stock_locate() const { return stock_locate_; }
void PayloadOrderDeleteMessage::set_stock_locate(std::uint16_t value) { stock_locate_ = value; }

std::uint16_t PayloadOrderDeleteMessage::tracking_number() const { return tracking_number_; }
void PayloadOrderDeleteMessage::set_tracking_number(std::uint16_t value) { tracking_number_ = value; }

std::chrono::nanoseconds PayloadOrderDeleteMessage::timestamp() const { return timestamp_; }
void PayloadOrderDeleteMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint64_t PayloadOrderDeleteMessage::order_reference_number() const { return order_reference_number_; }
void PayloadOrderDeleteMessage::set_order_reference_number(std::uint64_t value) { order_reference_number_ = value; }

PacketMessageCode PayloadOrderDeleteMessage::type() const { return message_type; }

std::string_view PayloadOrderDeleteMessage::name() const { return "Order Delete Message"; }

std::size_t PayloadOrderDeleteMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadOrderDeleteMessage", wire_size, length);

    stock_locate_ = wire::read_u16_be(data + offset);
    offset += 2;

    tracking_number_ = wire::read_u16_be(data + offset);
    offset += 2;

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u48_be(data + offset)));
    offset += 6;

    order_reference_number_ = wire::read_u64_be(data + offset);
    offset += 8;

    return offset;
}

std::size_t PayloadOrderDeleteMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadOrderDeleteMessage", wire_size, capacity);

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(stock_locate_));
    offset += 2;

    wire::write_u16_be(data + offset, static_cast<std::uint16_t>(tracking_number_));
    offset += 2;

    wire::write_u48_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 6;

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(order_reference_number_));
    offset += 8;

    return offset;
}

std::size_t PayloadOrderDeleteMessage::encoded_size() const {
    return wire_size;
}

void PayloadOrderDeleteMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadOrderDeleteMessage::clone() const {
    return std::make_unique<PayloadOrderDeleteMessage>(*this);
}

void PayloadOrderDeleteMessage::print(std::ostream& out) const {
    out << "PayloadOrderDeleteMessage{";
    out << "stock_locate=";
    out << stock_locate_;
    out << ", tracking_number=";
    out << tracking_number_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", order_reference_number=";
    out << order_reference_number_;
    out << '}';
}

bool PayloadOrderDeleteMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadOrderDeleteMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadOrderDeleteMessage::operator==(const PayloadOrderDeleteMessage& other) const {
    return stock_locate_ == other.stock_locate_
        && tracking_number_ == other.tracking_number_
        && timestamp_ == other.timestamp_
        && order_reference_number_ == other.order_reference_number_;
}

bool PayloadOrderDeleteMessage::operator!=(const PayloadOrderDeleteMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
