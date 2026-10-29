#include "UnknownQuoteMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v1_91 {

UnknownQuoteMessagePayload::UnknownQuoteMessagePayload(QuoteMessagePayloadCode code) : type_(code) {}

UnknownQuoteMessagePayload::UnknownQuoteMessagePayload(QuoteMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownQuoteMessagePayload::set_type(QuoteMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownQuoteMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownQuoteMessagePayload::body() { return body_; }
void UnknownQuoteMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

QuoteMessagePayloadCode UnknownQuoteMessagePayload::type() const { return type_; }

std::string_view UnknownQuoteMessagePayload::name() const { return "Unknown QuoteMessagePayload"; }

std::size_t UnknownQuoteMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownQuoteMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownQuoteMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownQuoteMessagePayload::encoded_size() const { return body_.size(); }

void UnknownQuoteMessagePayload::accept(QuoteMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<QuoteMessagePayload> UnknownQuoteMessagePayload::clone() const { return std::make_unique<UnknownQuoteMessagePayload>(*this); }

void UnknownQuoteMessagePayload::print(std::ostream& out) const {
    out << "UnknownQuoteMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownQuoteMessagePayload::equals(const QuoteMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownQuoteMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownQuoteMessagePayload::operator==(const UnknownQuoteMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownQuoteMessagePayload::operator!=(const UnknownQuoteMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cqs::output::cta::v1_91
