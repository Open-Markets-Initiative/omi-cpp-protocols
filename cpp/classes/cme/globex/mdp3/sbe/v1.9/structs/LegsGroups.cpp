#include "LegsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

LegsGroups::LegsGroups(const GroupSize& group_size, const std::vector<LegsGroup>& legs_group)
  : group_size_(group_size), legs_group_(legs_group) {}

const GroupSize& LegsGroups::group_size() const { return group_size_; }
GroupSize& LegsGroups::group_size() { return group_size_; }
void LegsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<LegsGroup>& LegsGroups::legs_group() const { return legs_group_; }
std::vector<LegsGroup>& LegsGroups::legs_group() { return legs_group_; }
void LegsGroups::set_legs_group(const std::vector<LegsGroup>& value) { legs_group_ = value; }

std::size_t LegsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        legs_group_.clear();
        legs_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            LegsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("LegsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            legs_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t LegsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(legs_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(LegsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : legs_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LegsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(legs_group_);
}

void LegsGroups::print(std::ostream& out) const {
    out << "LegsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", legs_group=";
    print::sequence(out, legs_group_);
    out << '}';
}

bool LegsGroups::operator==(const LegsGroups& other) const {
    return group_size_ == other.group_size_
        && legs_group_ == other.legs_group_;
}

bool LegsGroups::operator!=(const LegsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
