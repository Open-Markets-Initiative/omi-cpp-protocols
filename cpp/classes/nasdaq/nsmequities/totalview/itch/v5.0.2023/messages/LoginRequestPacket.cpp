#include "LoginRequestPacket.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

LoginRequestPacket::LoginRequestPacket(const std::string& username, const std::string& password, const std::string& requested_session, const std::string& requested_sequence_number)
  : username_(username), password_(password), requested_session_(requested_session), requested_sequence_number_(requested_sequence_number) {}

const std::string& LoginRequestPacket::username() const { return username_; }
std::string& LoginRequestPacket::username() { return username_; }
void LoginRequestPacket::set_username(const std::string& value) { username_ = value; }

const std::string& LoginRequestPacket::password() const { return password_; }
std::string& LoginRequestPacket::password() { return password_; }
void LoginRequestPacket::set_password(const std::string& value) { password_ = value; }

const std::string& LoginRequestPacket::requested_session() const { return requested_session_; }
std::string& LoginRequestPacket::requested_session() { return requested_session_; }
void LoginRequestPacket::set_requested_session(const std::string& value) { requested_session_ = value; }

const std::string& LoginRequestPacket::requested_sequence_number() const { return requested_sequence_number_; }
std::string& LoginRequestPacket::requested_sequence_number() { return requested_sequence_number_; }
void LoginRequestPacket::set_requested_sequence_number(const std::string& value) { requested_sequence_number_ = value; }

MessageCode LoginRequestPacket::type() const { return message_type; }

std::string_view LoginRequestPacket::name() const { return "Login Request Packet"; }

std::size_t LoginRequestPacket::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("LoginRequestPacket", wire_size, length);

    username_ = wire::read_text(data + offset, 6, ' ');
    offset += 6;

    password_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    requested_session_ = wire::read_text(data + offset, 10, ' ');
    offset += 10;

    requested_sequence_number_ = wire::read_text(data + offset, 20, ' ');
    offset += 20;

    return offset;
}

std::size_t LoginRequestPacket::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LoginRequestPacket", wire_size, capacity);

    wire::write_text(data + offset, 6, ' ', username_);
    offset += 6;

    wire::write_text(data + offset, 10, ' ', password_);
    offset += 10;

    wire::write_text(data + offset, 10, ' ', requested_session_);
    offset += 10;

    wire::write_text(data + offset, 20, ' ', requested_sequence_number_);
    offset += 20;

    return offset;
}

std::size_t LoginRequestPacket::encoded_size() const {
    return wire_size;
}

void LoginRequestPacket::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> LoginRequestPacket::clone() const {
    return std::make_unique<LoginRequestPacket>(*this);
}

void LoginRequestPacket::print(std::ostream& out) const {
    out << "LoginRequestPacket{";
    out << "username=";
    print::text(out, username_);
    out << ", password=";
    print::text(out, password_);
    out << ", requested_session=";
    print::text(out, requested_session_);
    out << ", requested_sequence_number=";
    print::text(out, requested_sequence_number_);
    out << '}';
}

bool LoginRequestPacket::equals(const Message& other) const {
    const auto* that = dynamic_cast<const LoginRequestPacket*>(&other);
    return that != nullptr && *this == *that;
}

bool LoginRequestPacket::operator==(const LoginRequestPacket& other) const {
    return username_ == other.username_
        && password_ == other.password_
        && requested_session_ == other.requested_session_
        && requested_sequence_number_ == other.requested_sequence_number_;
}

bool LoginRequestPacket::operator!=(const LoginRequestPacket& other) const {
    return !(*this == other);
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
