#include "UnknownGatewayMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

UnknownGatewayMessage::UnknownGatewayMessage(GatewayMessageCode code) : type_(code) {}

UnknownGatewayMessage::UnknownGatewayMessage(GatewayMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownGatewayMessage::set_type(GatewayMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownGatewayMessage::body() const { return body_; }
std::vector<std::byte>& UnknownGatewayMessage::body() { return body_; }
void UnknownGatewayMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

GatewayMessageCode UnknownGatewayMessage::type() const { return type_; }

std::string_view UnknownGatewayMessage::name() const { return "Unknown GatewayMessage"; }

std::size_t UnknownGatewayMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownGatewayMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownGatewayMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownGatewayMessage::encoded_size() const { return body_.size(); }

void UnknownGatewayMessage::accept(GatewayMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<GatewayMessage> UnknownGatewayMessage::clone() const { return std::make_unique<UnknownGatewayMessage>(*this); }

void UnknownGatewayMessage::print(std::ostream& out) const {
    out << "UnknownGatewayMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownGatewayMessage::equals(const GatewayMessage& other) const {
    const auto* that = dynamic_cast<const UnknownGatewayMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownGatewayMessage::operator==(const UnknownGatewayMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownGatewayMessage::operator!=(const UnknownGatewayMessage& other) const { return !(*this == other); }

} // namespace databento::marketdata::normalized::dbn::v2
