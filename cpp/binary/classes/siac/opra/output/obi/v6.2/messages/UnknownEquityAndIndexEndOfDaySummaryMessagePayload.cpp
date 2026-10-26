#include "UnknownEquityAndIndexEndOfDaySummaryMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnknownEquityAndIndexEndOfDaySummaryMessagePayload::UnknownEquityAndIndexEndOfDaySummaryMessagePayload(EquityAndIndexEndOfDaySummaryMessagePayloadCode code) : type_(code) {}

UnknownEquityAndIndexEndOfDaySummaryMessagePayload::UnknownEquityAndIndexEndOfDaySummaryMessagePayload(EquityAndIndexEndOfDaySummaryMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownEquityAndIndexEndOfDaySummaryMessagePayload::set_type(EquityAndIndexEndOfDaySummaryMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownEquityAndIndexEndOfDaySummaryMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownEquityAndIndexEndOfDaySummaryMessagePayload::body() { return body_; }
void UnknownEquityAndIndexEndOfDaySummaryMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

EquityAndIndexEndOfDaySummaryMessagePayloadCode UnknownEquityAndIndexEndOfDaySummaryMessagePayload::type() const { return type_; }

std::string_view UnknownEquityAndIndexEndOfDaySummaryMessagePayload::name() const { return "Unknown EquityAndIndexEndOfDaySummaryMessagePayload"; }

std::size_t UnknownEquityAndIndexEndOfDaySummaryMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownEquityAndIndexEndOfDaySummaryMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownEquityAndIndexEndOfDaySummaryMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownEquityAndIndexEndOfDaySummaryMessagePayload::encoded_size() const { return body_.size(); }

void UnknownEquityAndIndexEndOfDaySummaryMessagePayload::accept(EquityAndIndexEndOfDaySummaryMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> UnknownEquityAndIndexEndOfDaySummaryMessagePayload::clone() const { return std::make_unique<UnknownEquityAndIndexEndOfDaySummaryMessagePayload>(*this); }

void UnknownEquityAndIndexEndOfDaySummaryMessagePayload::print(std::ostream& out) const {
    out << "UnknownEquityAndIndexEndOfDaySummaryMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownEquityAndIndexEndOfDaySummaryMessagePayload::equals(const EquityAndIndexEndOfDaySummaryMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownEquityAndIndexEndOfDaySummaryMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownEquityAndIndexEndOfDaySummaryMessagePayload::operator==(const UnknownEquityAndIndexEndOfDaySummaryMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownEquityAndIndexEndOfDaySummaryMessagePayload::operator!=(const UnknownEquityAndIndexEndOfDaySummaryMessagePayload& other) const { return !(*this == other); }

} // namespace siac::opra::output::obi::v6_2
