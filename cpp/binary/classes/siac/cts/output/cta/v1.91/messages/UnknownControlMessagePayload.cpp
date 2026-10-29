#include "UnknownControlMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v1_91 {

UnknownControlMessagePayload::UnknownControlMessagePayload(ControlMessagePayloadCode code) : type_(code) {}

UnknownControlMessagePayload::UnknownControlMessagePayload(ControlMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownControlMessagePayload::set_type(ControlMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownControlMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownControlMessagePayload::body() { return body_; }
void UnknownControlMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

ControlMessagePayloadCode UnknownControlMessagePayload::type() const { return type_; }

std::string_view UnknownControlMessagePayload::name() const { return "Unknown ControlMessagePayload"; }

std::size_t UnknownControlMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownControlMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownControlMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownControlMessagePayload::encoded_size() const { return body_.size(); }

void UnknownControlMessagePayload::accept(ControlMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<ControlMessagePayload> UnknownControlMessagePayload::clone() const { return std::make_unique<UnknownControlMessagePayload>(*this); }

void UnknownControlMessagePayload::print(std::ostream& out) const {
    out << "UnknownControlMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownControlMessagePayload::equals(const ControlMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownControlMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownControlMessagePayload::operator==(const UnknownControlMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownControlMessagePayload::operator!=(const UnknownControlMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cts::output::cta::v1_91
