#include "DebugPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

DebugPacket::DebugPacket(char debug_text)
  : debug_text_(debug_text) {}

char DebugPacket::debug_text() const { return debug_text_; }
void DebugPacket::set_debug_text(char value) { debug_text_ = value; }

MessageCode DebugPacket::type() const { return message_type; }

std::string_view DebugPacket::name() const { return "Debug Packet"; }

std::size_t DebugPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("DebugPacket", wire_size, length);

    debug_text_ = wire::read_char(data + offset);
    offset += 1;

    return offset;
}

std::size_t DebugPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DebugPacket", wire_size, capacity);

    wire::write_char(data + offset, debug_text_);
    offset += 1;

    return offset;
}

std::size_t DebugPacket::encoded_size() const {
    return wire_size;
}

void DebugPacket::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> DebugPacket::clone() const {
    return std::make_unique<DebugPacket>(*this);
}

void DebugPacket::print(std::ostream& out) const {
    out << "DebugPacket{";
    out << "debug_text=";
    print::character(out, debug_text_);
    out << '}';
}

bool DebugPacket::equals(const Message& other) const {
    const auto* that = dynamic_cast<const DebugPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool DebugPacket::operator==(const DebugPacket& other) const {
    return debug_text_ == other.debug_text_;
}

bool DebugPacket::operator!=(const DebugPacket& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
