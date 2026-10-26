#include "AdminLogout.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

AdminLogout::AdminLogout(const std::string& text)
  : text_(text) {}

const std::string& AdminLogout::text() const { return text_; }
std::string& AdminLogout::text() { return text_; }
void AdminLogout::set_text(const std::string& value) { text_ = value; }

MktdataPayloadCode AdminLogout::type() const { return message_type; }

std::string_view AdminLogout::name() const { return "Admin Logout"; }

std::size_t AdminLogout::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("AdminLogout", wire_size, length);

    text_ = wire::read_text(data + offset, 100, '\0');
    offset += 100;

    return offset;
}

std::size_t AdminLogout::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("AdminLogout", wire_size, capacity);

    wire::write_text(data + offset, 100, '\0', text_);
    offset += 100;

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
    out << "text=";
    print::text(out, text_);
    out << '}';
}

bool AdminLogout::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const AdminLogout*>(&other);
    return that != nullptr && *this == *that;
}

bool AdminLogout::operator==(const AdminLogout& other) const {
    return text_ == other.text_;
}

bool AdminLogout::operator!=(const AdminLogout& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
