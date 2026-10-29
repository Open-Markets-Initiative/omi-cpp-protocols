#include "SecurityListRequestRelatedSymbolGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

SecurityListRequestRelatedSymbolGroups::SecurityListRequestRelatedSymbolGroups(const GroupSize& group_size, const std::vector<SecurityListRequestRelatedSymbolGroup>& security_list_request_related_symbol_group)
  : group_size_(group_size), security_list_request_related_symbol_group_(security_list_request_related_symbol_group) {}

const GroupSize& SecurityListRequestRelatedSymbolGroups::group_size() const { return group_size_; }
GroupSize& SecurityListRequestRelatedSymbolGroups::group_size() { return group_size_; }
void SecurityListRequestRelatedSymbolGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SecurityListRequestRelatedSymbolGroup>& SecurityListRequestRelatedSymbolGroups::security_list_request_related_symbol_group() const { return security_list_request_related_symbol_group_; }
std::vector<SecurityListRequestRelatedSymbolGroup>& SecurityListRequestRelatedSymbolGroups::security_list_request_related_symbol_group() { return security_list_request_related_symbol_group_; }
void SecurityListRequestRelatedSymbolGroups::set_security_list_request_related_symbol_group(const std::vector<SecurityListRequestRelatedSymbolGroup>& value) { security_list_request_related_symbol_group_ = value; }

std::size_t SecurityListRequestRelatedSymbolGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        security_list_request_related_symbol_group_.clear();
        security_list_request_related_symbol_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SecurityListRequestRelatedSymbolGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SecurityListRequestRelatedSymbolGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            security_list_request_related_symbol_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SecurityListRequestRelatedSymbolGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityListRequestRelatedSymbolGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(security_list_request_related_symbol_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SecurityListRequestRelatedSymbolGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : security_list_request_related_symbol_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SecurityListRequestRelatedSymbolGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(security_list_request_related_symbol_group_);
}

void SecurityListRequestRelatedSymbolGroups::print(std::ostream& out) const {
    out << "SecurityListRequestRelatedSymbolGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", security_list_request_related_symbol_group=";
    print::sequence(out, security_list_request_related_symbol_group_);
    out << '}';
}

bool SecurityListRequestRelatedSymbolGroups::operator==(const SecurityListRequestRelatedSymbolGroups& other) const {
    return group_size_ == other.group_size_
        && security_list_request_related_symbol_group_ == other.security_list_request_related_symbol_group_;
}

bool SecurityListRequestRelatedSymbolGroups::operator!=(const SecurityListRequestRelatedSymbolGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SecurityListRequestRelatedSymbolGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
