#include "ServerPayloadDebugPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

ServerPayloadDebugPacket::ServerPayloadDebugPacket(const std::string& debug_text)
  : debug_text_(debug_text) {}

const std::string& ServerPayloadDebugPacket::debug_text() const { return debug_text_; }
std::string& ServerPayloadDebugPacket::debug_text() { return debug_text_; }
void ServerPayloadDebugPacket::set_debug_text(const std::string& value) { debug_text_ = value; }

ServerMessageCode ServerPayloadDebugPacket::type() const { return message_type; }

std::string_view ServerPayloadDebugPacket::name() const { return "Debug Packet"; }

std::size_t ServerPayloadDebugPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    {
        const std::size_t count = length - offset;
        wire::require("ServerPayloadDebugPacket", offset + count, length);
        debug_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t ServerPayloadDebugPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadDebugPacket", encoded_size(), capacity);

    wire::require_capacity("encode", offset + debug_text_.size(), capacity);
    wire::write_text(data + offset, debug_text_.size(), ' ', debug_text_);
    offset += debug_text_.size();

    return offset;
}

std::size_t ServerPayloadDebugPacket::encoded_size() const {
    return debug_text_.size();
}

void ServerPayloadDebugPacket::accept(ServerMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerMessage> ServerPayloadDebugPacket::clone() const {
    return std::make_unique<ServerPayloadDebugPacket>(*this);
}

void ServerPayloadDebugPacket::print(std::ostream& out) const {
    out << "ServerPayloadDebugPacket{";
    out << "debug_text=";
    print::text(out, debug_text_);
    out << '}';
}

bool ServerPayloadDebugPacket::equals(const ServerMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadDebugPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadDebugPacket::operator==(const ServerPayloadDebugPacket& other) const {
    return debug_text_ == other.debug_text_;
}

bool ServerPayloadDebugPacket::operator!=(const ServerPayloadDebugPacket& other) const {
    return !(*this == other);
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
