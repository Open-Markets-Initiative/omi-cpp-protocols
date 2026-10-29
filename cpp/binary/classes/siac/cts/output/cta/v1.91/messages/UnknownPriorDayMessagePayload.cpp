#include "UnknownPriorDayMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v1_91 {

UnknownPriorDayMessagePayload::UnknownPriorDayMessagePayload(PriorDayMessagePayloadCode code) : type_(code) {}

UnknownPriorDayMessagePayload::UnknownPriorDayMessagePayload(PriorDayMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownPriorDayMessagePayload::set_type(PriorDayMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownPriorDayMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownPriorDayMessagePayload::body() { return body_; }
void UnknownPriorDayMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

PriorDayMessagePayloadCode UnknownPriorDayMessagePayload::type() const { return type_; }

std::string_view UnknownPriorDayMessagePayload::name() const { return "Unknown PriorDayMessagePayload"; }

std::size_t UnknownPriorDayMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownPriorDayMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownPriorDayMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownPriorDayMessagePayload::encoded_size() const { return body_.size(); }

void UnknownPriorDayMessagePayload::accept(PriorDayMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<PriorDayMessagePayload> UnknownPriorDayMessagePayload::clone() const { return std::make_unique<UnknownPriorDayMessagePayload>(*this); }

void UnknownPriorDayMessagePayload::print(std::ostream& out) const {
    out << "UnknownPriorDayMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownPriorDayMessagePayload::equals(const PriorDayMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownPriorDayMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownPriorDayMessagePayload::operator==(const UnknownPriorDayMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownPriorDayMessagePayload::operator!=(const UnknownPriorDayMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cts::output::cta::v1_91
