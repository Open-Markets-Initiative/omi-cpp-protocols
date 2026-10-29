#include "NegotiateMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

NegotiateMessage::NegotiateMessage(std::uint32_t session_id, std::uint64_t session_ver_id, std::chrono::nanoseconds timestamp, std::uint32_t entering_firm, std::optional<std::uint32_t> onbehalf_firm, const Credentials& credentials, const ClientIp& client_ip, const ClientAppName& client_app_name, const ClientAppVersion& client_app_version)
  : session_id_(session_id), session_ver_id_(session_ver_id), timestamp_(timestamp), entering_firm_(entering_firm), onbehalf_firm_(onbehalf_firm), credentials_(credentials), client_ip_(client_ip), client_app_name_(client_app_name), client_app_version_(client_app_version) {}

std::uint32_t NegotiateMessage::session_id() const { return session_id_; }
void NegotiateMessage::set_session_id(std::uint32_t value) { session_id_ = value; }

std::uint64_t NegotiateMessage::session_ver_id() const { return session_ver_id_; }
void NegotiateMessage::set_session_ver_id(std::uint64_t value) { session_ver_id_ = value; }

std::chrono::nanoseconds NegotiateMessage::timestamp() const { return timestamp_; }
void NegotiateMessage::set_timestamp(std::chrono::nanoseconds value) { timestamp_ = value; }

std::uint32_t NegotiateMessage::entering_firm() const { return entering_firm_; }
void NegotiateMessage::set_entering_firm(std::uint32_t value) { entering_firm_ = value; }

std::optional<std::uint32_t> NegotiateMessage::onbehalf_firm() const { return onbehalf_firm_; }
void NegotiateMessage::set_onbehalf_firm(std::optional<std::uint32_t> value) { onbehalf_firm_ = value; }

const Credentials& NegotiateMessage::credentials() const { return credentials_; }
Credentials& NegotiateMessage::credentials() { return credentials_; }
void NegotiateMessage::set_credentials(const Credentials& value) { credentials_ = value; }

const ClientIp& NegotiateMessage::client_ip() const { return client_ip_; }
ClientIp& NegotiateMessage::client_ip() { return client_ip_; }
void NegotiateMessage::set_client_ip(const ClientIp& value) { client_ip_ = value; }

const ClientAppName& NegotiateMessage::client_app_name() const { return client_app_name_; }
ClientAppName& NegotiateMessage::client_app_name() { return client_app_name_; }
void NegotiateMessage::set_client_app_name(const ClientAppName& value) { client_app_name_ = value; }

const ClientAppVersion& NegotiateMessage::client_app_version() const { return client_app_version_; }
ClientAppVersion& NegotiateMessage::client_app_version() { return client_app_version_; }
void NegotiateMessage::set_client_app_version(const ClientAppVersion& value) { client_app_version_ = value; }

MessageCode NegotiateMessage::type() const { return message_type; }

std::string_view NegotiateMessage::name() const { return "Negotiate Message"; }

std::size_t NegotiateMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("NegotiateMessage", offset + 4, length);
    session_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("NegotiateMessage", offset + 8, length);
    session_ver_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("NegotiateMessage", offset + 8, length);
    timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("NegotiateMessage", offset + 4, length);
    entering_firm_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("NegotiateMessage", offset + 4, length);
    onbehalf_firm_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    offset += credentials_.decode(data + offset, length - offset);

    offset += client_ip_.decode(data + offset, length - offset);

    offset += client_app_name_.decode(data + offset, length - offset);

    offset += client_app_version_.decode(data + offset, length - offset);

    return offset;
}

std::size_t NegotiateMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("NegotiateMessage", encoded_size(), capacity);

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(session_id_));
    offset += 4;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(session_ver_id_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(timestamp_.count()));
    offset += 8;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(entering_firm_));
    offset += 4;

    wire::write_u32_le(data + offset, onbehalf_firm_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    offset += credentials_.encode(data + offset, capacity - offset);

    offset += client_ip_.encode(data + offset, capacity - offset);

    offset += client_app_name_.encode(data + offset, capacity - offset);

    offset += client_app_version_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t NegotiateMessage::encoded_size() const {
    return 4 + 8 + 8 + 4 + 4 + credentials_.encoded_size() + client_ip_.encoded_size() + client_app_name_.encoded_size() + client_app_version_.encoded_size();
}

void NegotiateMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> NegotiateMessage::clone() const {
    return std::make_unique<NegotiateMessage>(*this);
}

void NegotiateMessage::print(std::ostream& out) const {
    out << "NegotiateMessage{";
    out << "session_id=";
    out << session_id_;
    out << ", session_ver_id=";
    out << session_ver_id_;
    out << ", timestamp=";
    out << timestamp_.count();
    out << ", entering_firm=";
    out << entering_firm_;
    out << ", onbehalf_firm=";
    print::optional(out, onbehalf_firm_);
    out << ", credentials=";
    credentials_.print(out);
    out << ", client_ip=";
    client_ip_.print(out);
    out << ", client_app_name=";
    client_app_name_.print(out);
    out << ", client_app_version=";
    client_app_version_.print(out);
    out << '}';
}

bool NegotiateMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const NegotiateMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool NegotiateMessage::operator==(const NegotiateMessage& other) const {
    return session_id_ == other.session_id_
        && session_ver_id_ == other.session_ver_id_
        && timestamp_ == other.timestamp_
        && entering_firm_ == other.entering_firm_
        && onbehalf_firm_ == other.onbehalf_firm_
        && credentials_ == other.credentials_
        && client_ip_ == other.client_ip_
        && client_app_name_ == other.client_app_name_
        && client_app_version_ == other.client_app_version_;
}

bool NegotiateMessage::operator!=(const NegotiateMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
