#include "AdminLogout.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

AdminLogout::AdminLogout(const std::string& logout_text)
  : logout_text_(logout_text) {}

const std::string& AdminLogout::logout_text() const { return logout_text_; }
std::string& AdminLogout::logout_text() { return logout_text_; }
void AdminLogout::set_logout_text(const std::string& value) { logout_text_ = value; }

MktdataPayloadCode AdminLogout::type() const { return message_type; }

std::string_view AdminLogout::name() const { return "Admin Logout"; }

std::size_t AdminLogout::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AdminLogout", wire_size, length);

    logout_text_ = wire::read_text(data + offset, 180, '\0');
    offset += 180;

    return offset;
}

std::size_t AdminLogout::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AdminLogout", wire_size, capacity);

    wire::write_text(data + offset, 180, '\0', logout_text_);
    offset += 180;

    return offset;
}

std::size_t AdminLogout::encoded_size() const {
    return wire_size;
}

void AdminLogout::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> AdminLogout::clone() const {
    return std::make_unique<AdminLogout>(*this);
}

void AdminLogout::print(std::ostream& out) const {
    out << "AdminLogout{";
    out << "logout_text=";
    print::text(out, logout_text_);
    out << '}';
}

bool AdminLogout::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const AdminLogout*>(&other);
    return that != nullptr && *this == *that;
}

bool AdminLogout::operator==(const AdminLogout& other) const {
    return logout_text_ == other.logout_text_;
}

bool AdminLogout::operator!=(const AdminLogout& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
