#include "UnknownTradeMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::cts::output::cta::v2_9 {

UnknownTradeMessagePayload::UnknownTradeMessagePayload(TradeMessagePayloadCode code) : type_(code) {}

UnknownTradeMessagePayload::UnknownTradeMessagePayload(TradeMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownTradeMessagePayload::set_type(TradeMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownTradeMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownTradeMessagePayload::body() { return body_; }
void UnknownTradeMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

TradeMessagePayloadCode UnknownTradeMessagePayload::type() const { return type_; }

std::string_view UnknownTradeMessagePayload::name() const { return "Unknown TradeMessagePayload"; }

std::size_t UnknownTradeMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownTradeMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownTradeMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownTradeMessagePayload::encoded_size() const { return body_.size(); }

void UnknownTradeMessagePayload::accept(TradeMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<TradeMessagePayload> UnknownTradeMessagePayload::clone() const { return std::make_unique<UnknownTradeMessagePayload>(*this); }

void UnknownTradeMessagePayload::print(std::ostream& out) const {
    out << "UnknownTradeMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownTradeMessagePayload::equals(const TradeMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownTradeMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownTradeMessagePayload::operator==(const UnknownTradeMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownTradeMessagePayload::operator!=(const UnknownTradeMessagePayload& other) const { return !(*this == other); }

} // namespace siac::cts::output::cta::v2_9
