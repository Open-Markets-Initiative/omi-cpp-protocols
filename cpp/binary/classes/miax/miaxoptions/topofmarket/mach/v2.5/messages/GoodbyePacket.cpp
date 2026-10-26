#include "GoodbyePacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

GoodbyePacket::GoodbyePacket(LogoutReason logout_reason, const std::string& logout_text)
  : logout_reason_(logout_reason), logout_text_(logout_text) {}

LogoutReason GoodbyePacket::logout_reason() const { return logout_reason_; }
void GoodbyePacket::set_logout_reason(LogoutReason value) { logout_reason_ = value; }

const std::string& GoodbyePacket::logout_text() const { return logout_text_; }
std::string& GoodbyePacket::logout_text() { return logout_text_; }
void GoodbyePacket::set_logout_text(const std::string& value) { logout_text_ = value; }

TcpMessageCode GoodbyePacket::type() const { return message_type; }

std::string_view GoodbyePacket::name() const { return "Goodbye Packet"; }

std::size_t GoodbyePacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("GoodbyePacket", offset + 1, length);
    logout_reason_ = static_cast<LogoutReason>(wire::read_char(data + offset));
    offset += 1;

    {
        const std::size_t count = length - offset;
        wire::require("GoodbyePacket", offset + count, length);
        logout_text_.assign(reinterpret_cast<const char*>(data + offset), count);
        offset += count;
    }

    return offset;
}

std::size_t GoodbyePacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("GoodbyePacket", encoded_size(), capacity);

    wire::write_char(data + offset, static_cast<char>(logout_reason_));
    offset += 1;

    wire::require_capacity("encode", offset + logout_text_.size(), capacity);
    wire::write_text(data + offset, logout_text_.size(), ' ', logout_text_);
    offset += logout_text_.size();

    return offset;
}

std::size_t GoodbyePacket::encoded_size() const {
    return 1 + logout_text_.size();
}

void GoodbyePacket::accept(TcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<TcpMessage> GoodbyePacket::clone() const {
    return std::make_unique<GoodbyePacket>(*this);
}

void GoodbyePacket::print(std::ostream& out) const {
    out << "GoodbyePacket{";
    out << "logout_reason=";
    out << logout_reason_;
    out << ", logout_text=";
    print::text(out, logout_text_);
    out << '}';
}

bool GoodbyePacket::equals(const TcpMessage& other) const {
    const auto* that = dynamic_cast<const GoodbyePacket*>(&other);
    return that != nullptr && *this == *that;
}

bool GoodbyePacket::operator==(const GoodbyePacket& other) const {
    return logout_reason_ == other.logout_reason_
        && logout_text_ == other.logout_text_;
}

bool GoodbyePacket::operator!=(const GoodbyePacket& other) const {
    return !(*this == other);
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
