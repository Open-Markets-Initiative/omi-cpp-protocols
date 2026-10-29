#include "NegotiateResponseMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

NegotiateResponseMessage::NegotiateResponseMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds request_timestamp, std::uint32_t entering_firm, const SemanticVersion& semantic_version)
  : session_id_(session_id), session_ver_id_(session_ver_id), request_timestamp_(request_timestamp), entering_firm_(entering_firm), semantic_version_(semantic_version) {}

std::uint32_t NegotiateResponseMessage::session_id() const { return session_id_; }
void NegotiateResponseMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t NegotiateResponseMessage::session_ver_id() const { return session_ver_id_; }
void NegotiateResponseMessage::set_session_ver_id(std::uint64_t value) { session_ver_id_ = value; }

std::chrono::nanoseconds NegotiateResponseMessage::request_timestamp() const { return request_timestamp_; }
void NegotiateResponseMessage::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

std::uint32_t NegotiateResponseMessage::entering_firm() const { return entering_firm_; }
void NegotiateResponseMessage::set_entering_firm(std::uint32_t value) { entering_firm_ = value; }

const SemanticVersion& NegotiateResponseMessage::semantic_version() const { return semantic_version_; }
SemanticVersion& NegotiateResponseMessage::semantic_version() { return semantic_version_; }
void NegotiateResponseMessage::set_semantic_version(const SemanticVersion& value) { semantic_version_ = value; }

MessageCode NegotiateResponseMessage::type() const { return message_type; }

std::string_view NegotiateResponseMessage::name() const { return "Negotiate Response Message"; }

std::size_t NegotiateResponseMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("NegotiateResponseMessage", wire_size, length);

    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    session_ver_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    entering_firm_ = wire::read_u32_le(data + offset);
    offset += 4;

    offset += semantic_version_.decode(data + offset, length - offset);

    return offset;
}

std::size_t NegotiateResponseMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NegotiateResponseMessage", wire_size, capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(session_ver_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(entering_firm_));
    offset += 4;

    offset += semantic_version_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t NegotiateResponseMessage::encoded_size() const {
    return wire_size;
}

void NegotiateResponseMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NegotiateResponseMessage::clone() const {
    return std::make_unique<NegotiateResponseMessage>(*this);
}

void NegotiateResponseMessage::print(std::ostream& out) const {
    out << "NegotiateResponseMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", session_ver_id=";
    out << session_ver_id_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", entering_firm=";
    out << entering_firm_;
    out << ", semantic_version=";
    semantic_version_.print(out);
    out << '}';
}

bool NegotiateResponseMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NegotiateResponseMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NegotiateResponseMessage::operator==(const NegotiateResponseMessage& other) const {
    return session_id_ == other.session_id_
        && session_ver_id_ == other.session_ver_id_
        && request_timestamp_ == other.request_timestamp_
        && entering_firm_ == other.entering_firm_
        && semantic_version_ == other.semantic_version_;
}

bool NegotiateResponseMessage::operator!=(const NegotiateResponseMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
