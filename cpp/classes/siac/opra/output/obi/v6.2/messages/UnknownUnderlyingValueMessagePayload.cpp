#include "UnknownUnderlyingValueMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnknownUnderlyingValueMessagePayload::UnknownUnderlyingValueMessagePayload(UnderlyingValueMessagePayloadCode code) : type_(code) {}

UnknownUnderlyingValueMessagePayload::UnknownUnderlyingValueMessagePayload(UnderlyingValueMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownUnderlyingValueMessagePayload::set_type(UnderlyingValueMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownUnderlyingValueMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownUnderlyingValueMessagePayload::body() { return body_; }
void UnknownUnderlyingValueMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

UnderlyingValueMessagePayloadCode UnknownUnderlyingValueMessagePayload::type() const { return type_; }

std::string_view UnknownUnderlyingValueMessagePayload::name() const { return "Unknown UnderlyingValueMessagePayload"; }

std::size_t UnknownUnderlyingValueMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownUnderlyingValueMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownUnderlyingValueMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownUnderlyingValueMessagePayload::encoded_size() const { return body_.size(); }

void UnknownUnderlyingValueMessagePayload::accept(UnderlyingValueMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<UnderlyingValueMessagePayload> UnknownUnderlyingValueMessagePayload::clone() const { return std::make_unique<UnknownUnderlyingValueMessagePayload>(*this); }

void UnknownUnderlyingValueMessagePayload::print(std::ostream& out) const {
    out << "UnknownUnderlyingValueMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownUnderlyingValueMessagePayload::equals(const UnderlyingValueMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownUnderlyingValueMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownUnderlyingValueMessagePayload::operator==(const UnknownUnderlyingValueMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownUnderlyingValueMessagePayload::operator!=(const UnknownUnderlyingValueMessagePayload& other) const { return !(*this == other); }

} // namespace siac::opra::output::obi::v6_2
