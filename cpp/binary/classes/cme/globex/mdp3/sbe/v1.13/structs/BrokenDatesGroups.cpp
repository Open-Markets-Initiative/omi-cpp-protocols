#include "BrokenDatesGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

BrokenDatesGroups::BrokenDatesGroups(const GroupSize& group_size, const std::vector<BrokenDatesGroup>& broken_dates_group)
  : group_size_(group_size), broken_dates_group_(broken_dates_group) {}

const GroupSize& BrokenDatesGroups::group_size() const { return group_size_; }
GroupSize& BrokenDatesGroups::group_size() { return group_size_; }
void BrokenDatesGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<BrokenDatesGroup>& BrokenDatesGroups::broken_dates_group() const { return broken_dates_group_; }
std::vector<BrokenDatesGroup>& BrokenDatesGroups::broken_dates_group() { return broken_dates_group_; }
void BrokenDatesGroups::set_broken_dates_group(const std::vector<BrokenDatesGroup>& value) { broken_dates_group_ = value; }

std::size_t BrokenDatesGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        broken_dates_group_.clear();
        broken_dates_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            BrokenDatesGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("BrokenDatesGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            broken_dates_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t BrokenDatesGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("BrokenDatesGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(broken_dates_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(BrokenDatesGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : broken_dates_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t BrokenDatesGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(broken_dates_group_);
}

void BrokenDatesGroups::print(std::ostream& out) const {
    out << "BrokenDatesGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", broken_dates_group=";
    print::sequence(out, broken_dates_group_);
    out << '}';
}

bool BrokenDatesGroups::operator==(const BrokenDatesGroups& other) const {
    return group_size_ == other.group_size_
        && broken_dates_group_ == other.broken_dates_group_;
}

bool BrokenDatesGroups::operator!=(const BrokenDatesGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const BrokenDatesGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
