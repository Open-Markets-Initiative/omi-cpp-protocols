#include "LoginAcceptedPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

LoginAcceptedPacket::LoginAcceptedPacket(const std::string& accepted_session, const std::string& accepted_sequence_number)
  : accepted_session_(accepted_session), accepted_sequence_number_(accepted_sequence_number) {}

const std::string& LoginAcceptedPacket::accepted_session() const { return accepted_session_; }
std::string& LoginAcceptedPacket::accepted_session() { return accepted_session_; }
void LoginAcceptedPacket::set_accepted_session(const std::string& value) { accepted_session_ = value; }

const std::string& LoginAcceptedPacket::accepted_sequence_number() const { return accepted_sequence_number_; }
std::string& LoginAcceptedPacket::accepted_sequence_number() { return accepted_sequence_number_; }
void LoginAcceptedPacket::set_accepted_sequence_number(const std::string& value) { accepted_sequence_number_ = value; }

ServerMessageCode LoginAcceptedPacket::type() const { return message_type; }

std::string_view LoginAcceptedPacket::name() const { return "Login Accepted Packet"; }

std::size_t LoginAcceptedPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginAcceptedPacket", wire_size, length);

    accepted_session_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    accepted_sequence_number_ = wire::read_text(data + offset, 20, ' ');
    offset += 20;

    return offset;
}

std::size_t LoginAcceptedPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginAcceptedPacket", wire_size, capacity);

    wire::write_text(data + offset, 10, ' ', accepted_session_);
    offset += 10;

    wire::write_text(data + offset, 20, ' ', accepted_sequence_number_);
    offset += 20;

    return offset;
}

std::size_t LoginAcceptedPacket::encoded_size() const {
    return wire_size;
}

void LoginAcceptedPacket::accept(ServerMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerMessage> LoginAcceptedPacket::clone() const {
    return std::make_unique<LoginAcceptedPacket>(*this);
}

void LoginAcceptedPacket::print(std::ostream& out) const {
    out << "LoginAcceptedPacket{";
    out << "accepted_session=";
    print::text(out, accepted_session_);
    out << ", accepted_sequence_number=";
    print::text(out, accepted_sequence_number_);
    out << '}';
}

bool LoginAcceptedPacket::equals(const ServerMessage& other) const {
    const auto* that = dynamic_cast<const LoginAcceptedPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginAcceptedPacket::operator==(const LoginAcceptedPacket& other) const {
    return accepted_session_ == other.accepted_session_
        && accepted_sequence_number_ == other.accepted_sequence_number_;
}

bool LoginAcceptedPacket::operator!=(const LoginAcceptedPacket& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
