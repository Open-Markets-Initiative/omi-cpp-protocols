#include "LegacyLegsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

LegacyLegsGroups::LegacyLegsGroups(const GroupSize& group_size, const std::vector<LegacyLegsGroup>& legacy_legs_group)
  : group_size_(group_size), legacy_legs_group_(legacy_legs_group) {}

const GroupSize& LegacyLegsGroups::group_size() const { return group_size_; }
GroupSize& LegacyLegsGroups::group_size() { return group_size_; }
void LegacyLegsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<LegacyLegsGroup>& LegacyLegsGroups::legacy_legs_group() const { return legacy_legs_group_; }
std::vector<LegacyLegsGroup>& LegacyLegsGroups::legacy_legs_group() { return legacy_legs_group_; }
void LegacyLegsGroups::set_legacy_legs_group(const std::vector<LegacyLegsGroup>& value) { legacy_legs_group_ = value; }

std::size_t LegacyLegsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        legacy_legs_group_.clear();
        legacy_legs_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            LegacyLegsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("LegacyLegsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            legacy_legs_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t LegacyLegsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("LegacyLegsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(legacy_legs_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(LegacyLegsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : legacy_legs_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LegacyLegsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(legacy_legs_group_);
}

void LegacyLegsGroups::print(std::ostream& out) const {
    out << "LegacyLegsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", legacy_legs_group=";
    print::sequence(out, legacy_legs_group_);
    out << '}';
}

bool LegacyLegsGroups::operator==(const LegacyLegsGroups& other) const {
    return group_size_ == other.group_size_
        && legacy_legs_group_ == other.legacy_legs_group_;
}

bool LegacyLegsGroups::operator!=(const LegacyLegsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegacyLegsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
