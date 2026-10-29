#include "TimeReferenceMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

TimeReferenceMessage::TimeReferenceMessage(std::uint32_t id, const std::array<std::byte, 4>& reserved_4, std::uint32_t source_time)
  : id_(id), reserved_4_(reserved_4), source_time_(source_time) {}

std::uint32_t TimeReferenceMessage::id() const { return id_; }
void TimeReferenceMessage::set_id(std::uint32_t value) { id_ = value; }

const std::array<std::byte, 4>& TimeReferenceMessage::reserved_4() const { return reserved_4_; }
std::array<std::byte, 4>& TimeReferenceMessage::reserved_4() { return reserved_4_; }
void TimeReferenceMessage::set_reserved_4(const std::array<std::byte, 4>& value) { reserved_4_ = value; }

std::uint32_t TimeReferenceMessage::source_time() const { return source_time_; }
void TimeReferenceMessage::set_source_time(std::uint32_t value) { source_time_ = value; }

MessageCode TimeReferenceMessage::type() const { return message_type; }

std::string_view TimeReferenceMessage::name() const { return "Time Reference Message"; }

std::size_t TimeReferenceMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TimeReferenceMessage", wire_size, length);

    id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::read_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    source_time_ = wire::read_u32_le(data + offset);
    offset += 4;

    return offset;
}

std::size_t TimeReferenceMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TimeReferenceMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(id_));
    offset += 4;

    wire::write_bytes(data + offset, reserved_4_.data(), 4);
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(source_time_));
    offset += 4;

    return offset;
}

std::size_t TimeReferenceMessage::encoded_size() const {
    return wire_size;
}

void TimeReferenceMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TimeReferenceMessage::clone() const {
    return std::make_unique<TimeReferenceMessage>(*this);
}

void TimeReferenceMessage::print(std::ostream& out) const {
    out << "TimeReferenceMessage{";
    out << "id=";
    out << id_;
    out << ", reserved_4=";
    print::hex(out, reserved_4_.data(), reserved_4_.size());
    out << ", source_time=";
    out << source_time_;
    out << '}';
}

bool TimeReferenceMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TimeReferenceMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TimeReferenceMessage::operator==(const TimeReferenceMessage& other) const {
    return id_ == other.id_
        && reserved_4_ == other.reserved_4_
        && source_time_ == other.source_time_;
}

bool TimeReferenceMessage::operator!=(const TimeReferenceMessage& other) const {
    return !(*this == other);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
