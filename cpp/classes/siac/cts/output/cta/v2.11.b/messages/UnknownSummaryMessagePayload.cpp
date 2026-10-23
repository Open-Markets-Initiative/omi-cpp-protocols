#include "UnknownSummaryMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_11_b {

UnknownSummaryMessagePayload::UnknownSummaryMessagePayload(SummaryMessagePayloadCode code) : type_(code) {}

UnknownSummaryMessagePayload::UnknownSummaryMessagePayload(SummaryMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownSummaryMessagePayload::set_type(SummaryMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownSummaryMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownSummaryMessagePayload::body() { return body_; }
void UnknownSummaryMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

SummaryMessagePayloadCode UnknownSummaryMessagePayload::type() const { return type_; }

std::string_view UnknownSummaryMessagePayload::name() const { return "Unknown SummaryMessagePayload"; }

std::size_t UnknownSummaryMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownSummaryMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownSummaryMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownSummaryMessagePayload::encoded_size() const { return body_.size(); }

void UnknownSummaryMessagePayload::accept(SummaryMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<SummaryMessagePayload> UnknownSummaryMessagePayload::clone() const { return std::make_unique<UnknownSummaryMessagePayload>(*this); }

void UnknownSummaryMessagePayload::print(std::ostream& out) const {
    out << "UnknownSummaryMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownSummaryMessagePayload::equals(const SummaryMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownSummaryMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownSummaryMessagePayload::operator==(const UnknownSummaryMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownSummaryMessagePayload::operator!=(const UnknownSummaryMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cts::output::cta::v2_11_b
