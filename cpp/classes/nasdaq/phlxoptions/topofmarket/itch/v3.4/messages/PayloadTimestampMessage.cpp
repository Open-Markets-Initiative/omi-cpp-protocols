#include "PayloadTimestampMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadTimestampMessage::PayloadTimestampMessage(std::chrono::seconds second)
  : second_(second) {}

std::chrono::seconds PayloadTimestampMessage::second() const { return second_; }
void PayloadTimestampMessage::set_second(std::chrono::seconds value) { second_ = value; }

PacketMessageCode PayloadTimestampMessage::type() const { return message_type; }

std::string_view PayloadTimestampMessage::name() const { return "Timestamp Message"; }

std::size_t PayloadTimestampMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadTimestampMessage", wire_size, length);

    second_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t PayloadTimestampMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadTimestampMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(second_.count()));
    offset += 4;

    return offset;
}

std::size_t PayloadTimestampMessage::encoded_size() const {
    return wire_size;
}

void PayloadTimestampMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadTimestampMessage::clone() const {
    return std::make_unique<PayloadTimestampMessage>(*this);
}

void PayloadTimestampMessage::print(std::ostream& out) const {
    out << "PayloadTimestampMessage{";
    out << "second=";
    out << second_.count();
    out << '}';
}

bool PayloadTimestampMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadTimestampMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadTimestampMessage::operator==(const PayloadTimestampMessage& other) const {
    return second_ == other.second_;
}

bool PayloadTimestampMessage::operator!=(const PayloadTimestampMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
