#include "UnknownShortEquityAndIndexQuoteMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnknownShortEquityAndIndexQuoteMessagePayload::UnknownShortEquityAndIndexQuoteMessagePayload(ShortEquityAndIndexQuoteMessagePayloadCode code) : type_(code) {}

UnknownShortEquityAndIndexQuoteMessagePayload::UnknownShortEquityAndIndexQuoteMessagePayload(ShortEquityAndIndexQuoteMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownShortEquityAndIndexQuoteMessagePayload::set_type(ShortEquityAndIndexQuoteMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownShortEquityAndIndexQuoteMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownShortEquityAndIndexQuoteMessagePayload::body() { return body_; }
void UnknownShortEquityAndIndexQuoteMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

ShortEquityAndIndexQuoteMessagePayloadCode UnknownShortEquityAndIndexQuoteMessagePayload::type() const { return type_; }

std::string_view UnknownShortEquityAndIndexQuoteMessagePayload::name() const { return "Unknown ShortEquityAndIndexQuoteMessagePayload"; }

std::size_t UnknownShortEquityAndIndexQuoteMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownShortEquityAndIndexQuoteMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownShortEquityAndIndexQuoteMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownShortEquityAndIndexQuoteMessagePayload::encoded_size() const { return body_.size(); }

void UnknownShortEquityAndIndexQuoteMessagePayload::accept(ShortEquityAndIndexQuoteMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> UnknownShortEquityAndIndexQuoteMessagePayload::clone() const { return std::make_unique<UnknownShortEquityAndIndexQuoteMessagePayload>(*this); }

void UnknownShortEquityAndIndexQuoteMessagePayload::print(std::ostream& out) const {
    out << "UnknownShortEquityAndIndexQuoteMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownShortEquityAndIndexQuoteMessagePayload::equals(const ShortEquityAndIndexQuoteMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownShortEquityAndIndexQuoteMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownShortEquityAndIndexQuoteMessagePayload::operator==(const UnknownShortEquityAndIndexQuoteMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownShortEquityAndIndexQuoteMessagePayload::operator!=(const UnknownShortEquityAndIndexQuoteMessagePayload& other) const { return !(*this == other); }

} // namespace siac::opra::output::obi::v6_2
