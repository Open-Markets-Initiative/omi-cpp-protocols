#include "TerminateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

TerminateMessage::TerminateMessage(std::uint32_t session_id, std::uint64_t session_ver_id, TerminationCode termination_code)
  : session_id_(session_id), session_ver_id_(session_ver_id), termination_code_(termination_code) {}

std::uint32_t TerminateMessage::session_id() const { return session_id_; }
void TerminateMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t TerminateMessage::session_ver_id() const { return session_ver_id_; }
void TerminateMessage::set_session_ver_id(std::uint64_t value) { session_ver_id_ = value; }

TerminationCode TerminateMessage::termination_code() const { return termination_code_; }
void TerminateMessage::set_termination_code(TerminationCode value) { termination_code_ = value; }

MessageCode TerminateMessage::type() const { return message_type; }

std::string_view TerminateMessage::name() const { return "Terminate Message"; }

std::size_t TerminateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("TerminateMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    session_ver_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    termination_code_ = static_cast<TerminationCode>(wire::read_u8(data + offset));
    offset += 1;

    return offset;
}

std::size_t TerminateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TerminateMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(session_ver_id_));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(termination_code_));
    offset += 1;

    return offset;
}

std::size_t TerminateMessage::encoded_size() const {
    return wire_size;
}

void TerminateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> TerminateMessage::clone() const {
    return std::make_unique<TerminateMessage>(*this);
}

void TerminateMessage::print(std::ostream& out) const {
    out << "TerminateMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", session_ver_id=";
    out << session_ver_id_;
    out << ", termination_code=";
    out << termination_code_;
    out << '}';
}

bool TerminateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const TerminateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool TerminateMessage::operator==(const TerminateMessage& other) const {
    return session_id_ == other.session_id_
        && session_ver_id_ == other.session_ver_id_
        && termination_code_ == other.termination_code_;
}

bool TerminateMessage::operator!=(const TerminateMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
