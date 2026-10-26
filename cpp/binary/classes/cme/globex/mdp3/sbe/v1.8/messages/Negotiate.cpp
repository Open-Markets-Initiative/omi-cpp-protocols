#include "Negotiate.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

Negotiate::Negotiate(const std::string& hmac_signature, const std::string& access_key_id, std::uint64_t uuid, std::chrono::nanoseconds request_timestamp, const std::string& session, const std::string& firm)
  : hmac_signature_(hmac_signature), access_key_id_(access_key_id), uuid_(uuid), request_timestamp_(request_timestamp), session_(session), firm_(firm) {}

const std::string& Negotiate::hmac_signature() const { return hmac_signature_; }
std::string& Negotiate::hmac_signature() { return hmac_signature_; }
void Negotiate::set_hmac_signature(const std::string& value) { hmac_signature_ = value; }

const std::string& Negotiate::access_key_id() const { return access_key_id_; }
std::string& Negotiate::access_key_id() { return access_key_id_; }
void Negotiate::set_access_key_id(const std::string& value) { access_key_id_ = value; }

std::uint64_t Negotiate::uuid() const { return uuid_; }
void Negotiate::set_uuid(std::uint64_t value) { uuid_ = value; }

std::chrono::nanoseconds Negotiate::request_timestamp() const { return request_timestamp_; }
void Negotiate::set_request_timestamp(std::chrono::nanoseconds value) { request_timestamp_ = value; }

const std::string& Negotiate::session() const { return session_; }
std::string& Negotiate::session() { return session_; }
void Negotiate::set_session(const std::string& value) { session_ = value; }

const std::string& Negotiate::firm() const { return firm_; }
std::string& Negotiate::firm() { return firm_; }
void Negotiate::set_firm(const std::string& value) { firm_ = value; }

MdpsessionmgmtPayloadCode Negotiate::type() const { return message_type; }

std::string_view Negotiate::name() const { return "Negotiate"; }

std::size_t Negotiate::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("Negotiate", wire_size, length);

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

std::size_t Negotiate::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("Negotiate", wire_size, capacity);

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

std::size_t Negotiate::encoded_size() const {
    return wire_size;
}

void Negotiate::accept(MdpsessionmgmtPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MdpsessionmgmtPayload> Negotiate::clone() const {
    return std::make_unique<Negotiate>(*this);
}

void Negotiate::print(std::ostream& out) const {
    out << "Negotiate{";
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

bool Negotiate::equals(const MdpsessionmgmtPayload& other) const {
    const auto* that = dynamic_cast<const Negotiate*>(&other);
    return that != nullptr && *this == *that;
}

bool Negotiate::operator==(const Negotiate& other) const {
    return hmac_signature_ == other.hmac_signature_
        && access_key_id_ == other.access_key_id_
        && uuid_ == other.uuid_
        && request_timestamp_ == other.request_timestamp_
        && session_ == other.session_
        && firm_ == other.firm_;
}

bool Negotiate::operator!=(const Negotiate& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_8
