#include "UnknownEquityAndIndexLastSaleMessagePayload.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace siac::opra::output::obi::v6_2 {

UnknownEquityAndIndexLastSaleMessagePayload::UnknownEquityAndIndexLastSaleMessagePayload(EquityAndIndexLastSaleMessagePayloadCode code) : type_(code) {}

UnknownEquityAndIndexLastSaleMessagePayload::UnknownEquityAndIndexLastSaleMessagePayload(EquityAndIndexLastSaleMessagePayloadCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownEquityAndIndexLastSaleMessagePayload::set_type(EquityAndIndexLastSaleMessagePayloadCode code) { type_ = code; }

const std::vector<std::byte>& UnknownEquityAndIndexLastSaleMessagePayload::body() const { return body_; }
std::vector<std::byte>& UnknownEquityAndIndexLastSaleMessagePayload::body() { return body_; }
void UnknownEquityAndIndexLastSaleMessagePayload::set_body(const std::vector<std::byte>& value) { body_ = value; }

EquityAndIndexLastSaleMessagePayloadCode UnknownEquityAndIndexLastSaleMessagePayload::type() const { return type_; }

std::string_view UnknownEquityAndIndexLastSaleMessagePayload::name() const { return "Unknown EquityAndIndexLastSaleMessagePayload"; }

std::size_t UnknownEquityAndIndexLastSaleMessagePayload::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownEquityAndIndexLastSaleMessagePayload::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownEquityAndIndexLastSaleMessagePayload", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownEquityAndIndexLastSaleMessagePayload::encoded_size() const { return body_.size(); }

void UnknownEquityAndIndexLastSaleMessagePayload::accept(EquityAndIndexLastSaleMessagePayloadVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<EquityAndIndexLastSaleMessagePayload> UnknownEquityAndIndexLastSaleMessagePayload::clone() const { return std::make_unique<UnknownEquityAndIndexLastSaleMessagePayload>(*this); }

void UnknownEquityAndIndexLastSaleMessagePayload::print(std::ostream& out) const {
    out << "UnknownEquityAndIndexLastSaleMessagePayload{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownEquityAndIndexLastSaleMessagePayload::equals(const EquityAndIndexLastSaleMessagePayload& other) const {
    const auto* that = dynamic_cast<const UnknownEquityAndIndexLastSaleMessagePayload*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownEquityAndIndexLastSaleMessagePayload::operator==(const UnknownEquityAndIndexLastSaleMessagePayload& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownEquityAndIndexLastSaleMessagePayload::operator!=(const UnknownEquityAndIndexLastSaleMessagePayload& other) const { return !(*this == other); }

} // namespace siac::opra::output::obi::v6_2
