#include "UnknownIndicesMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_10 {

UnknownIndicesMessagePayload::UnknownIndicesMessagePayload(IndicesMessagePayloadCode code) : type_(code) {}

UnknownIndicesMessagePayload::UnknownIndicesMessagePayload(IndicesMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownIndicesMessagePayload::set_type(IndicesMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownIndicesMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownIndicesMessagePayload::body() { return body_; }
void UnknownIndicesMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

IndicesMessagePayloadCode UnknownIndicesMessagePayload::type() const { return type_; }

std::string_view UnknownIndicesMessagePayload::name() const { return "Unknown IndicesMessagePayload"; }

std::size_t UnknownIndicesMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownIndicesMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownIndicesMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownIndicesMessagePayload::encoded_size() const { return body_.size(); }

void UnknownIndicesMessagePayload::accept(IndicesMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<IndicesMessagePayload> UnknownIndicesMessagePayload::clone() const { return std::make_unique<UnknownIndicesMessagePayload>(*this); }

void UnknownIndicesMessagePayload::print(std::ostream& out) const {
    out << "UnknownIndicesMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownIndicesMessagePayload::equals(const IndicesMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownIndicesMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownIndicesMessagePayload::operator==(const UnknownIndicesMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownIndicesMessagePayload::operator!=(const UnknownIndicesMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cts::output::cta::v2_10
