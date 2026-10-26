#include "SecurityStatusWorkupGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SecurityStatusWorkupGroups::SecurityStatusWorkupGroups(const GroupSize& group_size, const std::vector<SecurityStatusWorkupGroup>& security_status_workup_group)
  : group_size_(group_size), security_status_workup_group_(security_status_workup_group) {}

const GroupSize& SecurityStatusWorkupGroups::group_size() const { return group_size_; }
GroupSize& SecurityStatusWorkupGroups::group_size() { return group_size_; }
void SecurityStatusWorkupGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SecurityStatusWorkupGroup>& SecurityStatusWorkupGroups::security_status_workup_group() const { return security_status_workup_group_; }
std::vector<SecurityStatusWorkupGroup>& SecurityStatusWorkupGroups::security_status_workup_group() { return security_status_workup_group_; }
void SecurityStatusWorkupGroups::set_security_status_workup_group(const std::vector<SecurityStatusWorkupGroup>& value) { security_status_workup_group_ = value; }

std::size_t SecurityStatusWorkupGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        security_status_workup_group_.clear();
        security_status_workup_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SecurityStatusWorkupGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SecurityStatusWorkupGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            security_status_workup_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SecurityStatusWorkupGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityStatusWorkupGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(security_status_workup_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SecurityStatusWorkupGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : security_status_workup_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SecurityStatusWorkupGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(security_status_workup_group_);
}

void SecurityStatusWorkupGroups::print(std::ostream& out) const {
    out << "SecurityStatusWorkupGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", security_status_workup_group=";
    print::sequence(out, security_status_workup_group_);
    out << '}';
}

bool SecurityStatusWorkupGroups::operator==(const SecurityStatusWorkupGroups& other) const {
    return group_size_ == other.group_size_
        && security_status_workup_group_ == other.security_status_workup_group_;
}

bool SecurityStatusWorkupGroups::operator!=(const SecurityStatusWorkupGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityStatusWorkupGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
