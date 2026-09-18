#include "UnknownTcpMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

UnknownTcpMessage::UnknownTcpMessage(TcpMessageCode code) : type_(code) {}

UnknownTcpMessage::UnknownTcpMessage(TcpMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownTcpMessage::set_type(TcpMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownTcpMessage::body() const { return body_; }
std::vector<std::byte>& UnknownTcpMessage::body() { return body_; }
void UnknownTcpMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

TcpMessageCode UnknownTcpMessage::type() const { return type_; }

std::string_view UnknownTcpMessage::name() const { return "Unknown TcpMessage"; }

std::size_t UnknownTcpMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownTcpMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownTcpMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownTcpMessage::encoded_size() const { return body_.size(); }

void UnknownTcpMessage::accept(TcpMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<TcpMessage> UnknownTcpMessage::clone() const { return std::make_unique<UnknownTcpMessage>(*this); }

void UnknownTcpMessage::print(std::ostream& out) const {
    out << "UnknownTcpMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownTcpMessage::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const UnknownTcpMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownTcpMessage::operator==(const UnknownTcpMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownTcpMessage::operator!=(const UnknownTcpMessage& other) const { return !(*this == other); }

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
