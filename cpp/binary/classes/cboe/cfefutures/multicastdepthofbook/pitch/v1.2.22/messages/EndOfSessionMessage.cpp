#include "EndOfSessionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

EndOfSessionMessage::EndOfSessionMessage(std::chrono::nanoseconds time_offset)
  : time_offset_(time_offset) {}

std::chrono::nanoseconds EndOfSessionMessage::time_offset() const { return time_offset_; }
void EndOfSessionMessage::set_time_offset(std::chrono::nanoseconds value) { time_offset_ = value; }

MessageCode EndOfSessionMessage::type() const { return message_type; }

std::string_view EndOfSessionMessage::name() const { return "End Of Session Message"; }

std::size_t EndOfSessionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("EndOfSessionMessage", wire_size, length);

    time_offset_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t EndOfSessionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("EndOfSessionMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(time_offset_.count()));
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
    out << "time_offset=";
    out << time_offset_.count();
    out << '}';
}

bool EndOfSessionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const EndOfSessionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool EndOfSessionMessage::operator==(const EndOfSessionMessage& other) const {
    return time_offset_ == other.time_offset_;
}

bool EndOfSessionMessage::operator!=(const EndOfSessionMessage& other) const {
    return !(*this == other);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
