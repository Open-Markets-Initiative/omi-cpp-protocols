#include "ServerPayloadAdminLogin.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ServerPayloadAdminLogin::ServerPayloadAdminLogin(std::int8_t heart_bt_int)
  : heart_bt_int_(heart_bt_int) {}

std::int8_t ServerPayloadAdminLogin::heart_bt_int() const { return heart_bt_int_; }
void ServerPayloadAdminLogin::set_heart_bt_int(std::int8_t value) { heart_bt_int_ = value; }

ServerTcpMessageCode ServerPayloadAdminLogin::type() const { return message_type; }

std::string_view ServerPayloadAdminLogin::name() const { return "Admin Login"; }

std::size_t ServerPayloadAdminLogin::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerPayloadAdminLogin", wire_size, length);

    heart_bt_int_ = wire::read_i8(data + offset);
    offset += 1;

    return offset;
}

std::size_t ServerPayloadAdminLogin::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadAdminLogin", wire_size, capacity);

    wire::write_i8(data + offset, static_cast<std::int8_t>(heart_bt_int_));
    offset += 1;

    return offset;
}

std::size_t ServerPayloadAdminLogin::encoded_size() const {
    return wire_size;
}

void ServerPayloadAdminLogin::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadAdminLogin::clone() const {
    return std::make_unique<ServerPayloadAdminLogin>(*this);
}

void ServerPayloadAdminLogin::print(std::ostream& out) const {
    out << "ServerPayloadAdminLogin{";
    out << "heart_bt_int=";
    out << static_cast<int>(heart_bt_int_);
    out << '}';
}

bool ServerPayloadAdminLogin::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadAdminLogin*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadAdminLogin::operator==(const ServerPayloadAdminLogin& other) const {
    return heart_bt_int_ == other.heart_bt_int_;
}

bool ServerPayloadAdminLogin::operator!=(const ServerPayloadAdminLogin& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
