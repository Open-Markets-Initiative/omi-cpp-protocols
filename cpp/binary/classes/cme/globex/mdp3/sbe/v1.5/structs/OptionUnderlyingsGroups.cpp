#include "OptionUnderlyingsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

OptionUnderlyingsGroups::OptionUnderlyingsGroups(const GroupSize& group_size, const std::vector<OptionUnderlyingsGroup>& option_underlyings_group)
  : group_size_(group_size), option_underlyings_group_(option_underlyings_group) {}

const GroupSize& OptionUnderlyingsGroups::group_size() const { return group_size_; }
GroupSize& OptionUnderlyingsGroups::group_size() { return group_size_; }
void OptionUnderlyingsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<OptionUnderlyingsGroup>& OptionUnderlyingsGroups::option_underlyings_group() const { return option_underlyings_group_; }
std::vector<OptionUnderlyingsGroup>& OptionUnderlyingsGroups::option_underlyings_group() { return option_underlyings_group_; }
void OptionUnderlyingsGroups::set_option_underlyings_group(const std::vector<OptionUnderlyingsGroup>& value) { option_underlyings_group_ = value; }

std::size_t OptionUnderlyingsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        option_underlyings_group_.clear();
        option_underlyings_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            OptionUnderlyingsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("OptionUnderlyingsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            option_underlyings_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t OptionUnderlyingsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("OptionUnderlyingsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(option_underlyings_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(OptionUnderlyingsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : option_underlyings_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t OptionUnderlyingsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(option_underlyings_group_);
}

void OptionUnderlyingsGroups::print(std::ostream& out) const {
    out << "OptionUnderlyingsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", option_underlyings_group=";
    print::sequence(out, option_underlyings_group_);
    out << '}';
}

bool OptionUnderlyingsGroups::operator==(const OptionUnderlyingsGroups& other) const {
    return group_size_ == other.group_size_
        && option_underlyings_group_ == other.option_underlyings_group_;
}

bool OptionUnderlyingsGroups::operator!=(const OptionUnderlyingsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const OptionUnderlyingsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_5
