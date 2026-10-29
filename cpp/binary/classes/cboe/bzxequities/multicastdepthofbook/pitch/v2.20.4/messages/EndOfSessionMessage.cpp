#include "EndOfSessionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

EndOfSessionMessage::EndOfSessionMessage(std::uint32_t timestamp)
  : timestamp_(timestamp) {}

std::uint32_t EndOfSessionMessage::timestamp() const { return timestamp_; }
void EndOfSessionMessage::set_timestamp(std::uint32_t value) { timestamp_ = value; }

MessageCode EndOfSessionMessage::type() const { return message_type; }

std::string_view EndOfSessionMessage::name() const { return "End Of Session Message"; }

std::size_t EndOfSessionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfSessionMessage", wire_size, length);

    timestamp_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t EndOfSessionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfSessionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(timestamp_));
    offset += 4;

    return offset;
}

std::size_t EndOfSessionMessage::encoded_size() const {
    return wire_size;
}

void EndOfSessionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> EndOfSessionMessage::clone() const {
    return std::make_unique<EndOfSessionMessage>(*this);
}

void EndOfSessionMessage::print(std::ostream& out) const {
    out << "EndOfSessionMessage{";
    out << "timestamp=";
    out << timestamp_;
    out << '}';
}

bool EndOfSessionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfSessionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfSessionMessage::operator==(const EndOfSessionMessage& other) const {
    return timestamp_ == other.timestamp_;
}

bool EndOfSessionMessage::operator!=(const EndOfSessionMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
