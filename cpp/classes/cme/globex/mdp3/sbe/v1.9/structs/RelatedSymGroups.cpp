#include "RelatedSymGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

RelatedSymGroups::RelatedSymGroups(const GroupSize& group_size, const std::vector<RelatedSymGroup>& related_sym_group)
  : group_size_(group_size), related_sym_group_(related_sym_group) {}

const GroupSize& RelatedSymGroups::group_size() const { return group_size_; }
GroupSize& RelatedSymGroups::group_size() { return group_size_; }
void RelatedSymGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<RelatedSymGroup>& RelatedSymGroups::related_sym_group() const { return related_sym_group_; }
std::vector<RelatedSymGroup>& RelatedSymGroups::related_sym_group() { return related_sym_group_; }
void RelatedSymGroups::set_related_sym_group(const std::vector<RelatedSymGroup>& value) { related_sym_group_ = value; }

std::size_t RelatedSymGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        related_sym_group_.clear();
        related_sym_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            RelatedSymGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("RelatedSymGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            related_sym_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t RelatedSymGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("RelatedSymGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(related_sym_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(RelatedSymGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : related_sym_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t RelatedSymGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(related_sym_group_);
}

void RelatedSymGroups::print(std::ostream& out) const {
    out << "RelatedSymGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", related_sym_group=";
    print::sequence(out, related_sym_group_);
    out << '}';
}

bool RelatedSymGroups::operator==(const RelatedSymGroups& other) const {
    return group_size_ == other.group_size_
        && related_sym_group_ == other.related_sym_group_;
}

bool RelatedSymGroups::operator!=(const RelatedSymGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const RelatedSymGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
