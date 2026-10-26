#include "SystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

SystemEventMessage::SystemEventMessage(std::chrono::nanoseconds timestamp, EventCode event_code, SourceVenue source_venue)
  : timestamp_(timestamp), event_code_(event_code), source_venue_(source_venue) {}

std::chrono::nanoseconds SystemEventMessage::timestamp() const { return timestamp_; }
void SystemEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

EventCode SystemEventMessage::event_code() const { return event_code_; }
void SystemEventMessage::set_event_code(EventCode value) { event_code_ = value; }

SourceVenue SystemEventMessage::source_venue() const { return source_venue_; }
void SystemEventMessage::set_source_venue(SourceVenue value) { source_venue_ = value; }

MessageCode SystemEventMessage::type() const { return message_type; }

std::string_view SystemEventMessage::name() const { return "System Event Message"; }

std::size_t SystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemEventMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    event_code_ = static_cast<EventCode>(wire::read_char(data + offset));
    offset += 1;

    source_venue_ = static_cast<SourceVenue>(wire::read_u16_le(data + offset));
    offset += 2;

    return offset;
}

std::size_t SystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemEventMessage", wire_size, capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(event_code_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(source_venue_));
    offset += 2;

    return offset;
}

std::size_t SystemEventMessage::encoded_size() const {
    return wire_size;
}

void SystemEventMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SystemEventMessage::clone() const {
    return std::make_unique<SystemEventMessage>(*this);
}

void SystemEventMessage::print(std::ostream& out) const {
    out << "SystemEventMessage{";
    out << "timestamp=";
    out << timestamp_.count();
    out << ", event_code=";
    out << event_code_;
    out << ", source_venue=";
    out << source_venue_;
    out << '}';
}

bool SystemEventMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemEventMessage::operator==(const SystemEventMessage& other) const {
    return timestamp_ == other.timestamp_
        && event_code_ == other.event_code_
        && source_venue_ == other.source_venue_;
}

bool SystemEventMessage::operator!=(const SystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
