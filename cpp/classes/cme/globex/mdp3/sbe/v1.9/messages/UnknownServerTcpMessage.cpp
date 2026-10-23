#include "UnknownServerTcpMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

UnknownServerTcpMessage::UnknownServerTcpMessage(ServerTcpMessageCode code) : type_(code) {}

UnknownServerTcpMessage::UnknownServerTcpMessage(ServerTcpMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownServerTcpMessage::set_type(ServerTcpMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownServerTcpMessage::body() const { return body_; }
std::vector<std::byte>& UnknownServerTcpMessage::body() { return body_; }
void UnknownServerTcpMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

ServerTcpMessageCode UnknownServerTcpMessage::type() const { return type_; }

std::string_view UnknownServerTcpMessage::name() const { return "Unknown ServerTcpMessage"; }

std::size_t UnknownServerTcpMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownServerTcpMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownServerTcpMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownServerTcpMessage::encoded_size() const { return body_.size(); }

void UnknownServerTcpMessage::accept(ServerTcpMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<ServerTcpMessage> UnknownServerTcpMessage::clone() const { return std::make_unique<UnknownServerTcpMessage>(*this); }

void UnknownServerTcpMessage::print(std::ostream& out) const {
    out << "UnknownServerTcpMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownServerTcpMessage::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const UnknownServerTcpMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownServerTcpMessage::operator==(const UnknownServerTcpMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownServerTcpMessage::operator!=(const UnknownServerTcpMessage& other) const { return !(*this == other); }

} // namespace cme::globex::mdp3::sbe::v1_9
