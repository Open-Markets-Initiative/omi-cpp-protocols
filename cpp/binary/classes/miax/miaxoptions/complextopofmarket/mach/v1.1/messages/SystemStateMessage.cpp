#include "SystemStateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

SystemStateMessage::SystemStateMessage(std::chrono::nanoseconds nanoseconds, const std::string& c_to_m_version, std::uint32_t session_id, SystemStatus system_status)
  : nanoseconds_(nanoseconds), c_to_m_version_(c_to_m_version), session_id_(session_id), system_status_(system_status) {}

std::chrono::nanoseconds SystemStateMessage::nanoseconds() const { return nanoseconds_; }
void SystemStateMessage::set_nanoseconds(std::chrono::nanoseconds value) { nanoseconds_ = value; }

const std::string& SystemStateMessage::c_to_m_version() const { return c_to_m_version_; }
std::string& SystemStateMessage::c_to_m_version() { return c_to_m_version_; }
void SystemStateMessage::set_c_to_m_version(const std::string& value) { c_to_m_version_ = value; }

std::uint32_t SystemStateMessage::session_id() const { return session_id_; }
void SystemStateMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

SystemStatus SystemStateMessage::system_status() const { return system_status_; }
void SystemStateMessage::set_system_status(SystemStatus value) { system_status_ = value; }

DataCode SystemStateMessage::type() const { return message_type; }

std::string_view SystemStateMessage::name() const { return "System State Message"; }

std::size_t SystemStateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SystemStateMessage", wire_size, length);

    nanoseconds_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u32_le(data + offset)));
    offset += 4;

    c_to_m_version_ = wire::read_text(data + offset, 8, ' ');
    offset += 8;

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    system_status_ = static_cast<SystemStatus>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t SystemStateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SystemStateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(nanoseconds_.count()));
    offset += 4;

    wire::write_text(data + offset, 8, ' ', c_to_m_version_);
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(system_status_));
    offset += 1;

    return offset;
}

std::size_t SystemStateMessage::encoded_size() const {
    return wire_size;
}

void SystemStateMessage::accept(DataVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Data> SystemStateMessage::clone() const {
    return std::make_unique<SystemStateMessage>(*this);
}

void SystemStateMessage::print(std::ostream& out) const {
    out << "SystemStateMessage{";
    out << "nanoseconds=";
    out << nanoseconds_.count();
    out << ", c_to_m_version=";
    print::text(out, c_to_m_version_);
    out << ", session_id=";
    out << session_id_;
    out << ", system_status=";
    out << system_status_;
    out << '}';
}

bool SystemStateMessage::equals(const Data& other) const {
    const auto* that = dynamic_cast<const SystemStateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SystemStateMessage::operator==(const SystemStateMessage& other) const {
    return nanoseconds_ == other.nanoseconds_
        && c_to_m_version_ == other.c_to_m_version_
        && session_id_ == other.session_id_
        && system_status_ == other.system_status_;
}

bool SystemStateMessage::operator!=(const SystemStateMessage& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
