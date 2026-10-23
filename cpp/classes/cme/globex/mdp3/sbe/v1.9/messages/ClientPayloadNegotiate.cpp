#include "ClientPayloadNegotiate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ClientPayloadNegotiate::ClientPayloadNegotiate(const std::string& hmac_signature, const std::string& access_key_id, std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, const std::string& session, const std::string& firm)
  : hmac_signature_(hmac_signature), access_key_id_(access_key_id), uuid_(uuid), request_timestamp_(request_timestamp), session_(session), firm_(firm) {}

const std::string& ClientPayloadNegotiate::hmac_signature() const { return hmac_signature_; }
std::string& ClientPayloadNegotiate::hmac_signature() { return hmac_signature_; }
void ClientPayloadNegotiate::set_hmac_signature(const std::string& value) { hmac_signature_ = value; }

const std::string& ClientPayloadNegotiate::access_key_id() const { return access_key_id_; }
std::string& ClientPayloadNegotiate::access_key_id() { return access_key_id_; }
void ClientPayloadNegotiate::set_access_key_id(const std::string& value) { access_key_id_ = value; }

std::uint64_t ClientPayloadNegotiate::uuid() const { return uuid_; }
void ClientPayloadNegotiate::set_uuid(std::uint64_t value) { uuid_ = value; }

std::chrono::nanoseconds ClientPayloadNegotiate::request_timestamp() const { return request_timestamp_; }
void ClientPayloadNegotiate::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

const std::string& ClientPayloadNegotiate::session() const { return session_; }
std::string& ClientPayloadNegotiate::session() { return session_; }
void ClientPayloadNegotiate::set_session(const std::string& value) { session_ = value; }

const std::string& ClientPayloadNegotiate::firm() const { return firm_; }
std::string& ClientPayloadNegotiate::firm() { return firm_; }
void ClientPayloadNegotiate::set_firm(const std::string& value) { firm_ = value; }

ClientTcpMessageCode ClientPayloadNegotiate::type() const { return message_type; }

std::string_view ClientPayloadNegotiate::name() const { return "Negotiate"; }

std::size_t ClientPayloadNegotiate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ClientPayloadNegotiate", wire_size, length);

    hmac_signature_ = wire::read_text(data + offset, 32, '\0');
    offset += 32;

    access_key_id_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    uuid_ = wire::read_u64_le(data + offset);
    offset += 8;

    request_timestamp_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    session_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    firm_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    return offset;
}

std::size_t ClientPayloadNegotiate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ClientPayloadNegotiate", wire_size, capacity);

    wire::write_text(data + offset, 32, '\0', hmac_signature_);
    offset += 32;

    wire::write_text(data + offset, 20, '\0', access_key_id_);
    offset += 20;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(uuid_));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(request_timestamp_.count()));
    offset += 8;

    wire::write_text(data + offset, 5, '\0', session_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', firm_);
    offset += 5;

    return offset;
}

std::size_t ClientPayloadNegotiate::encoded_size() const {
    return wire_size;
}

void ClientPayloadNegotiate::accept(ClientTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ClientTcpMessage> ClientPayloadNegotiate::clone() const {
    return std::make_unique<ClientPayloadNegotiate>(*this);
}

void ClientPayloadNegotiate::print(std::ostream& out) const {
    out << "ClientPayloadNegotiate{";
    out << "hmac_signature=";
    print::text(out, hmac_signature_);
    out << ", access_key_id=";
    print::text(out, access_key_id_);
    out << ", uuid=";
    out << uuid_;
    out << ", request_timestamp=";
    out << request_timestamp_.count();
    out << ", session=";
    print::text(out, session_);
    out << ", firm=";
    print::text(out, firm_);
    out << '}';
}

bool ClientPayloadNegotiate::equals(const ClientTcpMessage& other) const {
    const auto* that = dynamic_cast<const ClientPayloadNegotiate*>(&other);
    return that != nullptr && *this == *that;
}

bool ClientPayloadNegotiate::operator==(const ClientPayloadNegotiate& other) const {
    return hmac_signature_ == other.hmac_signature_
        && access_key_id_ == other.access_key_id_
        && uuid_ == other.uuid_
        && request_timestamp_ == other.request_timestamp_
        && session_ == other.session_
        && firm_ == other.firm_;
}

bool ClientPayloadNegotiate::operator!=(const ClientPayloadNegotiate& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
