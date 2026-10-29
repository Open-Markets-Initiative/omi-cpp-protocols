#include "UnknownMarketStatusMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cqs::output::cta::v1_91 {

UnknownMarketStatusMessagePayload::UnknownMarketStatusMessagePayload(MarketStatusMessagePayloadCode code) : type_(code) {}

UnknownMarketStatusMessagePayload::UnknownMarketStatusMessagePayload(MarketStatusMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownMarketStatusMessagePayload::set_type(MarketStatusMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownMarketStatusMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownMarketStatusMessagePayload::body() { return body_; }
void UnknownMarketStatusMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

MarketStatusMessagePayloadCode UnknownMarketStatusMessagePayload::type() const { return type_; }

std::string_view UnknownMarketStatusMessagePayload::name() const { return "Unknown MarketStatusMessagePayload"; }

std::size_t UnknownMarketStatusMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownMarketStatusMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownMarketStatusMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownMarketStatusMessagePayload::encoded_size() const { return body_.size(); }

void UnknownMarketStatusMessagePayload::accept(MarketStatusMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<MarketStatusMessagePayload> UnknownMarketStatusMessagePayload::clone() const { return std::make_unique<UnknownMarketStatusMessagePayload>(*this); }

void UnknownMarketStatusMessagePayload::print(std::ostream& out) const {
    out << "UnknownMarketStatusMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownMarketStatusMessagePayload::equals(const MarketStatusMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownMarketStatusMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownMarketStatusMessagePayload::operator==(const UnknownMarketStatusMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownMarketStatusMessagePayload::operator!=(const UnknownMarketStatusMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cqs::output::cta::v1_91
