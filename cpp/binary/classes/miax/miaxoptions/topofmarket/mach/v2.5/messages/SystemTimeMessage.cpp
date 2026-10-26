#include "SystemTimeMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

SystemTimeMessage::SystemTimeMessage(std::chrono::seconds seconds)
  : seconds_(seconds) {}

std::chrono::seconds SystemTimeMessage::seconds() const { return seconds_; }
void SystemTimeMessage::set_seconds(std::chrono::seconds value) { seconds_ = value; }

DataCode SystemTimeMessage::type() const { return message_type; }

std::string_view SystemTimeMessage::name() const { return "System Time Message"; }

std::size_t SystemTimeMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemTimeMessage", wire_size, length);

    seconds_ = std::chrono::seconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    return offset;
}

std::size_t SystemTimeMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemTimeMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(seconds_.count()));
    offset += 4;

    return offset;
}

std::size_t SystemTimeMessage::encoded_size() const {
    return wire_size;
}

void SystemTimeMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SystemTimeMessage::clone() const {
    return std::make_unique<SystemTimeMessage>(*this);
}

void SystemTimeMessage::print(std::ostream& out) const {
    out << "SystemTimeMessage{";
    out << "seconds=";
    out << seconds_.count();
    out << '}';
}

bool SystemTimeMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SystemTimeMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemTimeMessage::operator==(const SystemTimeMessage& other) const {
    return seconds_ == other.seconds_;
}

bool SystemTimeMessage::operator!=(const SystemTimeMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
