#include "SecondsMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

SecondsMessage::SecondsMessage(std::chrono::seconds seconds)
  : seconds_(seconds) {}

std::chrono::seconds SecondsMessage::seconds() const { return seconds_; }
void SecondsMessage::set_seconds(std::chrono::seconds value) { seconds_ = value; }

MessageCode SecondsMessage::type() const { return message_type; }

std::string_view SecondsMessage::name() const { return "Seconds Message"; }

std::size_t SecondsMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecondsMessage", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t SecondsMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecondsMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    return offset;
}

std::size_t SecondsMessage::encoded_size() const {
    return wire_size;
}

void SecondsMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecondsMessage::clone() const {
    return std::make_unique<SecondsMessage>(*this);
}

void SecondsMessage::print(std::ostream& out) const {
    out << "SecondsMessage{";
    out << "seconds=";
    out << seconds_.count();
    out << '}';
}

bool SecondsMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecondsMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecondsMessage::operator==(const SecondsMessage& other) const {
    return seconds_ == other.seconds_;
}

bool SecondsMessage::operator!=(const SecondsMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
