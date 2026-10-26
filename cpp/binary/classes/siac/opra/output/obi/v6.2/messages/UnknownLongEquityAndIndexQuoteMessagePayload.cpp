#include "UnknownLongEquityAndIndexQuoteMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnknownLongEquityAndIndexQuoteMessagePayload::UnknownLongEquityAndIndexQuoteMessagePayload(LongEquityAndIndexQuoteMessagePayloadCode code) : type_(code) {}

UnknownLongEquityAndIndexQuoteMessagePayload::UnknownLongEquityAndIndexQuoteMessagePayload(LongEquityAndIndexQuoteMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownLongEquityAndIndexQuoteMessagePayload::set_type(LongEquityAndIndexQuoteMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownLongEquityAndIndexQuoteMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownLongEquityAndIndexQuoteMessagePayload::body() { return body_; }
void UnknownLongEquityAndIndexQuoteMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

LongEquityAndIndexQuoteMessagePayloadCode UnknownLongEquityAndIndexQuoteMessagePayload::type() const { return type_; }

std::string_view UnknownLongEquityAndIndexQuoteMessagePayload::name() const { return "Unknown LongEquityAndIndexQuoteMessagePayload"; }

std::size_t UnknownLongEquityAndIndexQuoteMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownLongEquityAndIndexQuoteMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownLongEquityAndIndexQuoteMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownLongEquityAndIndexQuoteMessagePayload::encoded_size() const { return body_.size(); }

void UnknownLongEquityAndIndexQuoteMessagePayload::accept(LongEquityAndIndexQuoteMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> UnknownLongEquityAndIndexQuoteMessagePayload::clone() const { return std::make_unique<UnknownLongEquityAndIndexQuoteMessagePayload>(*this); }

void UnknownLongEquityAndIndexQuoteMessagePayload::print(std::ostream& out) const {
    out << "UnknownLongEquityAndIndexQuoteMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownLongEquityAndIndexQuoteMessagePayload::equals(const LongEquityAndIndexQuoteMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownLongEquityAndIndexQuoteMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownLongEquityAndIndexQuoteMessagePayload::operator==(const UnknownLongEquityAndIndexQuoteMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownLongEquityAndIndexQuoteMessagePayload::operator!=(const UnknownLongEquityAndIndexQuoteMessagePayload& other) const { return !(*this == other); }

} // namespace siac::opra::output::obi::v6_2
