#include "UnknownServerMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

UnknownServerMessage::UnknownServerMessage(ServerMessageCode code) : type_(code) {}

UnknownServerMessage::UnknownServerMessage(ServerMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownServerMessage::set_type(ServerMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownServerMessage::body() const { return body_; }
std::vector<std::byte>& UnknownServerMessage::body() { return body_; }
void UnknownServerMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

ServerMessageCode UnknownServerMessage::type() const { return type_; }

std::string_view UnknownServerMessage::name() const { return "Unknown ServerMessage"; }

std::size_t UnknownServerMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownServerMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownServerMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownServerMessage::encoded_size() const { return body_.size(); }

void UnknownServerMessage::accept(ServerMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<ServerMessage> UnknownServerMessage::clone() const { return std::make_unique<UnknownServerMessage>(*this); }

void UnknownServerMessage::print(std::ostream& out) const {
    out << "UnknownServerMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownServerMessage::equals(const ServerMessage& other) const {
    const auto* that = dynamic_cast<const UnknownServerMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownServerMessage::operator==(const UnknownServerMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownServerMessage::operator!=(const UnknownServerMessage& other) const { return !(*this == other); }

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
