#include "SecurityListRequestSecurityGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

SecurityListRequestSecurityGroups::SecurityListRequestSecurityGroups(const GroupSize& group_size, const std::vector<SecurityListRequestSecurityGroup>& security_list_request_security_group)
  : group_size_(group_size), security_list_request_security_group_(security_list_request_security_group) {}

const GroupSize& SecurityListRequestSecurityGroups::group_size() const { return group_size_; }
GroupSize& SecurityListRequestSecurityGroups::group_size() { return group_size_; }
void SecurityListRequestSecurityGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SecurityListRequestSecurityGroup>& SecurityListRequestSecurityGroups::security_list_request_security_group() const { return security_list_request_security_group_; }
std::vector<SecurityListRequestSecurityGroup>& SecurityListRequestSecurityGroups::security_list_request_security_group() { return security_list_request_security_group_; }
void SecurityListRequestSecurityGroups::set_security_list_request_security_group(const std::vector<SecurityListRequestSecurityGroup>& value) { security_list_request_security_group_ = value; }

std::size_t SecurityListRequestSecurityGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        security_list_request_security_group_.clear();
        security_list_request_security_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SecurityListRequestSecurityGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SecurityListRequestSecurityGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            security_list_request_security_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SecurityListRequestSecurityGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityListRequestSecurityGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(security_list_request_security_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SecurityListRequestSecurityGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : security_list_request_security_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SecurityListRequestSecurityGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(security_list_request_security_group_);
}

void SecurityListRequestSecurityGroups::print(std::ostream& out) const {
    out << "SecurityListRequestSecurityGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", security_list_request_security_group=";
    print::sequence(out, security_list_request_security_group_);
    out << '}';
}

bool SecurityListRequestSecurityGroups::operator==(const SecurityListRequestSecurityGroups& other) const {
    return group_size_ == other.group_size_
        && security_list_request_security_group_ == other.security_list_request_security_group_;
}

bool SecurityListRequestSecurityGroups::operator!=(const SecurityListRequestSecurityGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityListRequestSecurityGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
