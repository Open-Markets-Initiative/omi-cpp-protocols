#include "ServerPayloadDebugPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

ServerPayloadDebugPacket::ServerPayloadDebugPacket(char debug_text)
  : debug_text_(debug_text) {}

char ServerPayloadDebugPacket::debug_text() const { return debug_text_; }
void ServerPayloadDebugPacket::set_debug_text(char value) { debug_text_ = value; }

ServerMessageCode ServerPayloadDebugPacket::type() const { return message_type; }

std::string_view ServerPayloadDebugPacket::name() const { return "Debug Packet"; }

std::size_t ServerPayloadDebugPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerPayloadDebugPacket", wire_size, length);

    debug_text_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t ServerPayloadDebugPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadDebugPacket", wire_size, capacity);

    wire::write_char(data + offset, debug_text_);
    offset += 1;

    return offset;
}

std::size_t ServerPayloadDebugPacket::encoded_size() const {
    return wire_size;
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
    print::character(out, debug_text_);
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

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
