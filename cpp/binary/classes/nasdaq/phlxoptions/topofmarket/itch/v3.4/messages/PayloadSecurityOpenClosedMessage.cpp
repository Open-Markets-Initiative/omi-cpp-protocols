#include "PayloadSecurityOpenClosedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

PayloadSecurityOpenClosedMessage::PayloadSecurityOpenClosedMessage(std::chrono::nanoseconds nanoseconds, std::uint32_t option_id, OpenState open_state)
  : nanoseconds_(nanoseconds), option_id_(option_id), open_state_(open_state) {}

std::chrono::nanoseconds PayloadSecurityOpenClosedMessage::nanoseconds() const { return nanoseconds_; }
void PayloadSecurityOpenClosedMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

std::uint32_t PayloadSecurityOpenClosedMessage::option_id() const { return option_id_; }
void PayloadSecurityOpenClosedMessage::set_option_id(std::uint32_t value) { option_id_ = value; }

OpenState PayloadSecurityOpenClosedMessage::open_state() const { return open_state_; }
void PayloadSecurityOpenClosedMessage::set_open_state(OpenState value) { open_state_ = value; }

PacketMessageCode PayloadSecurityOpenClosedMessage::type() const { return message_type; }

std::string_view PayloadSecurityOpenClosedMessage::name() const { return "Security Open Closed Message"; }

std::size_t PayloadSecurityOpenClosedMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("PayloadSecurityOpenClosedMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    option_id_ = wire::read_u32_be(data + offset);
    offset += 4;

    open_state_ = static_cast<OpenState>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t PayloadSecurityOpenClosedMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PayloadSecurityOpenClosedMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(option_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(open_state_));
    offset += 1;

    return offset;
}

std::size_t PayloadSecurityOpenClosedMessage::encoded_size() const {
    return wire_size;
}

void PayloadSecurityOpenClosedMessage::accept(PacketMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<PacketMessage> PayloadSecurityOpenClosedMessage::clone() const {
    return std::make_unique<PayloadSecurityOpenClosedMessage>(*this);
}

void PayloadSecurityOpenClosedMessage::print(std::ostream& out) const {
    out << "PayloadSecurityOpenClosedMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", option_id=";
    out << option_id_;
    out << ", open_state=";
    out << open_state_;
    out << '}';
}

bool PayloadSecurityOpenClosedMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const PayloadSecurityOpenClosedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool PayloadSecurityOpenClosedMessage::operator==(const PayloadSecurityOpenClosedMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && option_id_ == other.option_id_
        && open_state_ == other.open_state_;
}

bool PayloadSecurityOpenClosedMessage::operator!=(const PayloadSecurityOpenClosedMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
