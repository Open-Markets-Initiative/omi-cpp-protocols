#include "LoginRejectedPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

LoginRejectedPacket::LoginRejectedPacket(RejectReasonCode reject_reason_code)
  : reject_reason_code_(reject_reason_code) {}

RejectReasonCode LoginRejectedPacket::reject_reason_code() const { return reject_reason_code_; }
void LoginRejectedPacket::set_reject_reason_code(RejectReasonCode value) { reject_reason_code_ = value; }

ServerMessageCode LoginRejectedPacket::type() const { return message_type; }

std::string_view LoginRejectedPacket::name() const { return "Login Rejected Packet"; }

std::size_t LoginRejectedPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginRejectedPacket", wire_size, length);

    reject_reason_code_ = static_cast<RejectReasonCode>(wire::read_char(data + offset));
    offset += 1;

    return offset;
}

std::size_t LoginRejectedPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginRejectedPacket", wire_size, capacity);

    wire::write_char(data + offset, static_cast<char>(reject_reason_code_));
    offset += 1;

    return offset;
}

std::size_t LoginRejectedPacket::encoded_size() const {
    return wire_size;
}

void LoginRejectedPacket::accept(ServerMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerMessage> LoginRejectedPacket::clone() const {
    return std::make_unique<LoginRejectedPacket>(*this);
}

void LoginRejectedPacket::print(std::ostream& out) const {
    out << "LoginRejectedPacket{";
    out << "reject_reason_code=";
    out << reject_reason_code_;
    out << '}';
}

bool LoginRejectedPacket::equals(const ServerMessage& other) const {
    const auto* that = dynamic_cast<const LoginRejectedPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginRejectedPacket::operator==(const LoginRejectedPacket& other) const {
    return reject_reason_code_ == other.reject_reason_code_;
}

bool LoginRejectedPacket::operator!=(const LoginRejectedPacket& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
