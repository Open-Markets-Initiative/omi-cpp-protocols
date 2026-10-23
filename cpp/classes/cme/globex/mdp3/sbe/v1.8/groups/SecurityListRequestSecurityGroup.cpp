#include "SecurityListRequestSecurityGroup.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

SecurityListRequestSecurityGroup::SecurityListRequestSecurityGroup(const std::string& security_group)
  : security_group_(security_group) {}

const std::string& SecurityListRequestSecurityGroup::security_group() const { return security_group_; }
std::string& SecurityListRequestSecurityGroup::security_group() { return security_group_; }
void SecurityListRequestSecurityGroup::set_security_group(const std::string& value) { security_group_ = value; }

std::size_t SecurityListRequestSecurityGroup::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("SecurityListRequestSecurityGroup", wire_size, length);

    security_group_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    return offset;
}

std::size_t SecurityListRequestSecurityGroup::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityListRequestSecurityGroup", wire_size, capacity);

    wire::write_text(data + offset, 6, '\0', security_group_);
    offset += 6;

    return offset;
}

std::size_t SecurityListRequestSecurityGroup::encoded_size() const {
    return wire_size;
}

void SecurityListRequestSecurityGroup::print(std::ostream& out) const {
    out << "SecurityListRequestSecurityGroup{";
    out << "security_group=";
    print::text(out, security_group_);
    out << '}';
}

bool SecurityListRequestSecurityGroup::operator==(const SecurityListRequestSecurityGroup& other) const {
    return security_group_ == other.security_group_;
}

bool SecurityListRequestSecurityGroup::operator!=(const SecurityListRequestSecurityGroup& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityListRequestSecurityGroup& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
