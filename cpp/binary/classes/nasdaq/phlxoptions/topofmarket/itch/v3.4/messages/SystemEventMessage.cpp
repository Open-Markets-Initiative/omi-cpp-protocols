#include "SystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

SystemEventMessage::SystemEventMessage(std::chrono::nanoseconds nanoseconds, EventCode event_code, std::uint8_t version, std::uint8_t sub_version)
  : nanoseconds_(nanoseconds), event_code_(event_code), version_(version), sub_version_(sub_version) {}

std::chrono::nanoseconds SystemEventMessage::nanoseconds() const { return nanoseconds_; }
void SystemEventMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

EventCode SystemEventMessage::event_code() const { return event_code_; }
void SystemEventMessage::set_event_code(EventCode value) { event_code_ = value; }

std::uint8_t SystemEventMessage::version() const { return version_; }
void SystemEventMessage::set_version(std::uint8_t value) { version_ = value; }

std::uint8_t SystemEventMessage::sub_version() const { return sub_version_; }
void SystemEventMessage::set_sub_version(std::uint8_t value) { sub_version_ = value; }

SequencedMessageCode SystemEventMessage::type() const { return message_type; }

std::string_view SystemEventMessage::name() const { return "System Event Message"; }

std::size_t SystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemEventMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    event_code_ = static_cast<EventCode>(wire::read_char(data + offset));
    offset += 1;

    version_ = wire::read_u8(data + offset);
    offset += 1;

    sub_version_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t SystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemEventMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(event_code_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(version_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sub_version_));
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
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", event_code=";
    out << event_code_;
    out << ", version=";
    out << static_cast<int>(version_);
    out << ", sub_version=";
    out << static_cast<int>(sub_version_);
    out << '}';
}

bool SystemEventMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const SystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemEventMessage::operator==(const SystemEventMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && event_code_ == other.event_code_
        && version_ == other.version_
        && sub_version_ == other.sub_version_;
}

bool SystemEventMessage::operator!=(const SystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
