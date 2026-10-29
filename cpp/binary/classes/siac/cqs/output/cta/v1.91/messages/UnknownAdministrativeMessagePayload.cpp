#include "UnknownAdministrativeMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v1_91 {

UnknownAdministrativeMessagePayload::UnknownAdministrativeMessagePayload(AdministrativeMessagePayloadCode code) : type_(code) {}

UnknownAdministrativeMessagePayload::UnknownAdministrativeMessagePayload(AdministrativeMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownAdministrativeMessagePayload::set_type(AdministrativeMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownAdministrativeMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownAdministrativeMessagePayload::body() { return body_; }
void UnknownAdministrativeMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

AdministrativeMessagePayloadCode UnknownAdministrativeMessagePayload::type() const { return type_; }

std::string_view UnknownAdministrativeMessagePayload::name() const { return "Unknown AdministrativeMessagePayload"; }

std::size_t UnknownAdministrativeMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownAdministrativeMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownAdministrativeMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownAdministrativeMessagePayload::encoded_size() const { return body_.size(); }

void UnknownAdministrativeMessagePayload::accept(AdministrativeMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<AdministrativeMessagePayload> UnknownAdministrativeMessagePayload::clone() const { return std::make_unique<UnknownAdministrativeMessagePayload>(*this); }

void UnknownAdministrativeMessagePayload::print(std::ostream& out) const {
    out << "UnknownAdministrativeMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownAdministrativeMessagePayload::equals(const AdministrativeMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownAdministrativeMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownAdministrativeMessagePayload::operator==(const UnknownAdministrativeMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownAdministrativeMessagePayload::operator!=(const UnknownAdministrativeMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cqs::output::cta::v1_91
