#include "SystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

SystemEventMessage::SystemEventMessage(std::chrono::nanoseconds timestamp, SystemEvent system_event)
  : timestamp_(timestamp), system_event_(system_event) {}

std::chrono::nanoseconds SystemEventMessage::timestamp() const { return timestamp_; }
void SystemEventMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }
std::int64_t SystemEventMessage::timestamp_utc(const calendar::Day& day) const { return calendar::midnight(day, "Asia/Tokyo").utc(static_cast<std::int64_t>(timestamp_.count())); }

SystemEvent SystemEventMessage::system_event() const { return system_event_; }
void SystemEventMessage::set_system_event(SystemEvent value) { system_event_ = value; }

SequencedMessageCode SystemEventMessage::type() const { return message_type; }

std::string_view SystemEventMessage::name() const { return "System Event Message"; }

std::size_t SystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemEventMessage", wire_size, length);

    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_be(data + offset)));
    offset += 8;

    system_event_ = static_cast<SystemEvent>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemEventMessage", wire_size, capacity);

    wire::write_u64_be(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_char(data + offset, static_cast<char>(system_event_));
    offset += 1;

    return offset;
}

std::size_t SystemEventMessage::encoded_size() const {
    return wire_size;
}

void SystemEventMessage::accept(SequencedMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<SequencedMessage> SystemEventMessage::clone() const {
    return std::make_unique<SystemEventMessage>(*this);
}

void SystemEventMessage::print(std::ostream& out) const {
    out << "SystemEventMessage{";
    out << "timestamp=";
    calendar::print(out, timestamp_.count(), 1, "Asia/Tokyo");
    out << ", system_event=";
    out << system_event_;
    out << '}';
}

bool SystemEventMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const SystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemEventMessage::operator==(const SystemEventMessage& other) const {
    return timestamp_ == other.timestamp_
        && system_event_ == other.system_event_;
}

bool SystemEventMessage::operator!=(const SystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
