#include "SecondsTimestampMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

SecondsTimestampMessage::SecondsTimestampMessage(std::chrono::seconds time_seconds)
  : time_seconds_(time_seconds) {}

std::chrono::seconds SecondsTimestampMessage::time_seconds() const { return time_seconds_; }
void SecondsTimestampMessage::set_time_seconds(std::chrono::seconds value) { time_seconds_ = value; }

MessageCode SecondsTimestampMessage::type() const { return message_type; }

std::string_view SecondsTimestampMessage::name() const { return "Seconds Timestamp Message"; }

std::size_t SecondsTimestampMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecondsTimestampMessage", wire_size, length);

    time_seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    return offset;
}

std::size_t SecondsTimestampMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecondsTimestampMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(time_seconds_.count()));
    offset += 4;

    return offset;
}

std::size_t SecondsTimestampMessage::encoded_size() const {
    return wire_size;
}

void SecondsTimestampMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecondsTimestampMessage::clone() const {
    return std::make_unique<SecondsTimestampMessage>(*this);
}

void SecondsTimestampMessage::print(std::ostream& out) const {
    out << "SecondsTimestampMessage{";
    out << "time_seconds=";
    out << time_seconds_.count();
    out << '}';
}

bool SecondsTimestampMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecondsTimestampMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecondsTimestampMessage::operator==(const SecondsTimestampMessage& other) const {
    return time_seconds_ == other.time_seconds_;
}

bool SecondsTimestampMessage::operator!=(const SecondsTimestampMessage& other) const {
    return !(*this == other);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
