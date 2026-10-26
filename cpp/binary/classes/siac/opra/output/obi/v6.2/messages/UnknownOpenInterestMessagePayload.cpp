#include "UnknownOpenInterestMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnknownOpenInterestMessagePayload::UnknownOpenInterestMessagePayload(OpenInterestMessagePayloadCode code) : type_(code) {}

UnknownOpenInterestMessagePayload::UnknownOpenInterestMessagePayload(OpenInterestMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownOpenInterestMessagePayload::set_type(OpenInterestMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownOpenInterestMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownOpenInterestMessagePayload::body() { return body_; }
void UnknownOpenInterestMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

OpenInterestMessagePayloadCode UnknownOpenInterestMessagePayload::type() const { return type_; }

std::string_view UnknownOpenInterestMessagePayload::name() const { return "Unknown OpenInterestMessagePayload"; }

std::size_t UnknownOpenInterestMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownOpenInterestMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownOpenInterestMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownOpenInterestMessagePayload::encoded_size() const { return body_.size(); }

void UnknownOpenInterestMessagePayload::accept(OpenInterestMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<OpenInterestMessagePayload> UnknownOpenInterestMessagePayload::clone() const { return std::make_unique<UnknownOpenInterestMessagePayload>(*this); }

void UnknownOpenInterestMessagePayload::print(std::ostream& out) const {
    out << "UnknownOpenInterestMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownOpenInterestMessagePayload::equals(const OpenInterestMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownOpenInterestMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownOpenInterestMessagePayload::operator==(const UnknownOpenInterestMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownOpenInterestMessagePayload::operator!=(const UnknownOpenInterestMessagePayload& other) const { return !(*this == other); }

} // namespace siac::opra::output::obi::v6_2
