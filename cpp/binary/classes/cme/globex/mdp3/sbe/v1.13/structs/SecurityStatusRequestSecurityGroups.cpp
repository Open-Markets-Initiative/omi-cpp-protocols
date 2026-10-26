#include "SecurityStatusRequestSecurityGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SecurityStatusRequestSecurityGroups::SecurityStatusRequestSecurityGroups(const GroupSize& group_size, const std::vector<SecurityStatusRequestSecurityGroup>& security_status_request_security_group)
  : group_size_(group_size), security_status_request_security_group_(security_status_request_security_group) {}

const GroupSize& SecurityStatusRequestSecurityGroups::group_size() const { return group_size_; }
GroupSize& SecurityStatusRequestSecurityGroups::group_size() { return group_size_; }
void SecurityStatusRequestSecurityGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SecurityStatusRequestSecurityGroup>& SecurityStatusRequestSecurityGroups::security_status_request_security_group() const { return security_status_request_security_group_; }
std::vector<SecurityStatusRequestSecurityGroup>& SecurityStatusRequestSecurityGroups::security_status_request_security_group() { return security_status_request_security_group_; }
void SecurityStatusRequestSecurityGroups::set_security_status_request_security_group(const std::vector<SecurityStatusRequestSecurityGroup>& value) { security_status_request_security_group_ = value; }

std::size_t SecurityStatusRequestSecurityGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        security_status_request_security_group_.clear();
        security_status_request_security_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SecurityStatusRequestSecurityGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SecurityStatusRequestSecurityGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            security_status_request_security_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SecurityStatusRequestSecurityGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityStatusRequestSecurityGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(security_status_request_security_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SecurityStatusRequestSecurityGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : security_status_request_security_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SecurityStatusRequestSecurityGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(security_status_request_security_group_);
}

void SecurityStatusRequestSecurityGroups::print(std::ostream& out) const {
    out << "SecurityStatusRequestSecurityGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", security_status_request_security_group=";
    print::sequence(out, security_status_request_security_group_);
    out << '}';
}

bool SecurityStatusRequestSecurityGroups::operator==(const SecurityStatusRequestSecurityGroups& other) const {
    return group_size_ == other.group_size_
        && security_status_request_security_group_ == other.security_status_request_security_group_;
}

bool SecurityStatusRequestSecurityGroups::operator!=(const SecurityStatusRequestSecurityGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityStatusRequestSecurityGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
