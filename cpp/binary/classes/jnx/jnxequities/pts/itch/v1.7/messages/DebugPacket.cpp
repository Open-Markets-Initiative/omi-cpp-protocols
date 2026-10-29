#include "DebugPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

DebugPacket::DebugPacket(const std::string& debug_text)
  : debug_text_(debug_text) {}

const std::string& DebugPacket::debug_text() const { return debug_text_; }
std::string& DebugPacket::debug_text() { return debug_text_; }
void DebugPacket::set_debug_text(const std::string& value) { debug_text_ = value; }

MessageCode DebugPacket::type() const { return message_type; }

std::string_view DebugPacket::name() const { return "Debug Packet"; }

std::size_t DebugPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    {
        const std::size_t count = length - offset;
        wire::require("DebugPacket", offset + count, length);
        debug_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t DebugPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DebugPacket", encoded_size(), capacity);

    wire::require_capacity("encode", offset + debug_text_.size(), capacity);
    wire::write_text(data + offset, debug_text_.size(), ' ', debug_text_);
    offset += debug_text_.size();

    return offset;
}

std::size_t DebugPacket::encoded_size() const {
    return debug_text_.size();
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
    print::text(out, debug_text_);
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

} // namespace jnx::jnxequities::pts::itch::v1_7
