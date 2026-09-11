#include "UnknownMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

UnknownMessage::UnknownMessage(MessageCode code) : type_(code) {}

UnknownMessage::UnknownMessage(MessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownMessage::set_type(MessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownMessage::body() const { return body_; }
std::vector<std::byte>& UnknownMessage::body() { return body_; }
void UnknownMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

MessageCode UnknownMessage::type() const { return type_; }

std::string_view UnknownMessage::name() const { return "Unknown Message"; }

std::size_t UnknownMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownMessage::encoded_size() const { return body_.size(); }

void UnknownMessage::accept(Visitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<Message> UnknownMessage::clone() const { return std::make_unique<UnknownMessage>(*this); }

void UnknownMessage::print(std::ostream& out) const {
    out << "UnknownMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const UnknownMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownMessage::operator==(const UnknownMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownMessage::operator!=(const UnknownMessage& other) const { return !(*this == other); }

} // namespace iex::iexequities::deep::iextp::v1_08
