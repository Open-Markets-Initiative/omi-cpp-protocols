#include "UnknownClientTcpMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

UnknownClientTcpMessage::UnknownClientTcpMessage(ClientTcpMessageCode code) : type_(code) {}

UnknownClientTcpMessage::UnknownClientTcpMessage(ClientTcpMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownClientTcpMessage::set_type(ClientTcpMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownClientTcpMessage::body() const { return body_; }
std::vector<std::byte>& UnknownClientTcpMessage::body() { return body_; }
void UnknownClientTcpMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

ClientTcpMessageCode UnknownClientTcpMessage::type() const { return type_; }

std::string_view UnknownClientTcpMessage::name() const { return "Unknown ClientTcpMessage"; }

std::size_t UnknownClientTcpMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownClientTcpMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownClientTcpMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownClientTcpMessage::encoded_size() const { return body_.size(); }

void UnknownClientTcpMessage::accept(ClientTcpMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<ClientTcpMessage> UnknownClientTcpMessage::clone() const { return std::make_unique<UnknownClientTcpMessage>(*this); }

void UnknownClientTcpMessage::print(std::ostream& out) const {
    out << "UnknownClientTcpMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownClientTcpMessage::equals(const ClientTcpMessage& other) const {
    const auto* that = dynamic_cast<const UnknownClientTcpMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownClientTcpMessage::operator==(const UnknownClientTcpMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownClientTcpMessage::operator!=(const UnknownClientTcpMessage& other) const { return !(*this == other); }

} // namespace cme::globex::mdp3::sbe::v1_8
