#include "SystemEventMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

SystemEventMessage::SystemEventMessage(std::chrono::nanoseconds nanoseconds, const std::string& group, SystemEvent system_event)
  : nanoseconds_(nanoseconds), group_(group), system_event_(system_event) {}

std::chrono::nanoseconds SystemEventMessage::nanoseconds() const { return nanoseconds_; }
void SystemEventMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& SystemEventMessage::group() const { return group_; }
std::string& SystemEventMessage::group() { return group_; }
void SystemEventMessage::set_group(const std::string& value) { group_ = value; }

SystemEvent SystemEventMessage::system_event() const { return system_event_; }
void SystemEventMessage::set_system_event(SystemEvent value) { system_event_ = value; }

SequencedMessageCode SystemEventMessage::type() const { return message_type; }

std::string_view SystemEventMessage::name() const { return "System Event Message"; }

std::size_t SystemEventMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemEventMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_be(data + offset)));
    offset += 4;

    group_ = wire::read_text(data + offset, 4, ' ');
    offset += 4;

    system_event_ = static_cast<SystemEvent>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SystemEventMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemEventMessage", wire_size, capacity);

    wire::write_u32_be(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_text(data + offset, 4, ' ', group_);
    offset += 4;

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
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", group=";
    print::text(out, group_);
    out << ", system_event=";
    out << system_event_;
    out << '}';
}

bool SystemEventMessage::equals(const SequencedMessage& other) const {
    const auto* that = dynamic_cast<const SystemEventMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemEventMessage::operator==(const SystemEventMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && group_ == other.group_
        && system_event_ == other.system_event_;
}

bool SystemEventMessage::operator!=(const SystemEventMessage& other) const {
    return !(*this == other);
}

} // namespace jnx::jnxequities::pts::itch::v1_7
