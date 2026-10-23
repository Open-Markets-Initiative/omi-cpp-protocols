#include "ServerPayloadAdminLogout.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ServerPayloadAdminLogout::ServerPayloadAdminLogout(const std::string& logout_text)
  : logout_text_(logout_text) {}

const std::string& ServerPayloadAdminLogout::logout_text() const { return logout_text_; }
std::string& ServerPayloadAdminLogout::logout_text() { return logout_text_; }
void ServerPayloadAdminLogout::set_logout_text(const std::string& value) { logout_text_ = value; }

ServerTcpMessageCode ServerPayloadAdminLogout::type() const { return message_type; }

std::string_view ServerPayloadAdminLogout::name() const { return "Admin Logout"; }

std::size_t ServerPayloadAdminLogout::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerPayloadAdminLogout", wire_size, length);

    logout_text_ = wire::read_text(data + offset, 180, '\0');
    offset += 180;

    return offset;
}

std::size_t ServerPayloadAdminLogout::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadAdminLogout", wire_size, capacity);

    wire::write_text(data + offset, 180, '\0', logout_text_);
    offset += 180;

    return offset;
}

std::size_t ServerPayloadAdminLogout::encoded_size() const {
    return wire_size;
}

void ServerPayloadAdminLogout::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadAdminLogout::clone() const {
    return std::make_unique<ServerPayloadAdminLogout>(*this);
}

void ServerPayloadAdminLogout::print(std::ostream& out) const {
    out << "ServerPayloadAdminLogout{";
    out << "logout_text=";
    print::text(out, logout_text_);
    out << '}';
}

bool ServerPayloadAdminLogout::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadAdminLogout*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadAdminLogout::operator==(const ServerPayloadAdminLogout& other) const {
    return logout_text_ == other.logout_text_;
}

bool ServerPayloadAdminLogout::operator!=(const ServerPayloadAdminLogout& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
