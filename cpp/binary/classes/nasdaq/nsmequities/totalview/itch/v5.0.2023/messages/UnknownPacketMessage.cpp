#include "UnknownPacketMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

UnknownPacketMessage::UnknownPacketMessage(PacketMessageCode code) : type_(code) {}

UnknownPacketMessage::UnknownPacketMessage(PacketMessageCode code, const std::vector<std::byte>& body) : type_(code), body_(body) {}

void UnknownPacketMessage::set_type(PacketMessageCode code) { type_ = code; }

const std::vector<std::byte>& UnknownPacketMessage::body() const { return body_; }
std::vector<std::byte>& UnknownPacketMessage::body() { return body_; }
void UnknownPacketMessage::set_body(const std::vector<std::byte>& value) { body_ = value; }

PacketMessageCode UnknownPacketMessage::type() const { return type_; }

std::string_view UnknownPacketMessage::name() const { return "Unknown PacketMessage"; }

std::size_t UnknownPacketMessage::decode(const std::byte* data, std::size_t length) {
    body_.assign(data, data + length);
    return length;
}

std::size_t UnknownPacketMessage::encode(std::byte* data, std::size_t capacity) const {
    wire::require_capacity("UnknownPacketMessage", body_.size(), capacity);
    wire::write_bytes(data, body_.data(), body_.size());
    return body_.size();
}

std::size_t UnknownPacketMessage::encoded_size() const { return body_.size(); }

void UnknownPacketMessage::accept(PacketMessageVisitor& visitor) const { visitor.visit(*this); }

std::unique_ptr<PacketMessage> UnknownPacketMessage::clone() const { return std::make_unique<UnknownPacketMessage>(*this); }

void UnknownPacketMessage::print(std::ostream& out) const {
    out << "UnknownPacketMessage{type=" << type_ << ", body=";
    print::hex(out, body_.data(), body_.size());
    out << '}';
}

bool UnknownPacketMessage::equals(const PacketMessage& other) const {
    const auto* that = dynamic_cast<const UnknownPacketMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool UnknownPacketMessage::operator==(const UnknownPacketMessage& other) const { return type_ == other.type_ && body_ == other.body_; }
bool UnknownPacketMessage::operator!=(const UnknownPacketMessage& other) const { return !(*this == other); }

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
