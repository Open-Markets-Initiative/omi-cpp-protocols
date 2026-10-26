#include "UnknownUnsequencedMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

UnknownUnsequencedMessage::UnknownUnsequencedMessage(UnsequencedMessageCode code) : type_(code) {}

UnknownUnsequencedMessage::UnknownUnsequencedMessage(UnsequencedMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownUnsequencedMessage::set_type(UnsequencedMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownUnsequencedMessage::body() const { return body_; }
std::vector<std::byte>& UnknownUnsequencedMessage::body() { return body_; }
void UnknownUnsequencedMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

UnsequencedMessageCode UnknownUnsequencedMessage::type() const { return type_; }

std::string_view UnknownUnsequencedMessage::name() const { return "Unknown UnsequencedMessage"; }

std::size_t UnknownUnsequencedMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownUnsequencedMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownUnsequencedMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownUnsequencedMessage::encoded_size() const { return body_.size(); }

void UnknownUnsequencedMessage::accept(UnsequencedMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<UnsequencedMessage> UnknownUnsequencedMessage::clone() const { return std::make_unique<UnknownUnsequencedMessage>(*this); }

void UnknownUnsequencedMessage::print(std::ostream& out) const {
    out << "UnknownUnsequencedMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownUnsequencedMessage::equals(const UnsequencedMessage& other) const {
    const auto* that = dynamic_cast<const UnknownUnsequencedMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownUnsequencedMessage::operator==(const UnknownUnsequencedMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownUnsequencedMessage::operator!=(const UnknownUnsequencedMessage& other) const { return !(*this == other); }

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
