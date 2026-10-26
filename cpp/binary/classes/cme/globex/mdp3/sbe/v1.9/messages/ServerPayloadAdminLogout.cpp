#include "ServerPayloadAdminLogout.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ServerPayloadAdminLogout::ServerPayloadAdminLogout(const std::string& text)
  : text_(text) {}

const std::string& ServerPayloadAdminLogout::text() const { return text_; }
std::string& ServerPayloadAdminLogout::text() { return text_; }
void ServerPayloadAdminLogout::set_text(const std::string& value) { text_ = value; }

ServerTcpMessageCode ServerPayloadAdminLogout::type() const { return message_type; }

std::string_view ServerPayloadAdminLogout::name() const { return "Admin Logout"; }

std::size_t ServerPayloadAdminLogout::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("ServerPayloadAdminLogout", wire_size, length);

    text_ = wire::read_text(data + offset, 100, '\0');
    offset += 100;

    return offset;
}

std::size_t ServerPayloadAdminLogout::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadAdminLogout", wire_size, capacity);

    wire::write_text(data + offset, 100, '\0', text_);
    offset += 100;

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
    out << "text=";
    print::text(out, text_);
    out << '}';
}

bool ServerPayloadAdminLogout::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadAdminLogout*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadAdminLogout::operator==(const ServerPayloadAdminLogout& other) const {
    return text_ == other.text_;
}

bool ServerPayloadAdminLogout::operator!=(const ServerPayloadAdminLogout& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
