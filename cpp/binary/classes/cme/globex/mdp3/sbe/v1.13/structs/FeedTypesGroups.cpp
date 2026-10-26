#include "FeedTypesGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

FeedTypesGroups::FeedTypesGroups(const GroupSize& group_size, const std::vector<FeedTypesGroup>& feed_types_group)
  : group_size_(group_size), feed_types_group_(feed_types_group) {}

const GroupSize& FeedTypesGroups::group_size() const { return group_size_; }
GroupSize& FeedTypesGroups::group_size() { return group_size_; }
void FeedTypesGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<FeedTypesGroup>& FeedTypesGroups::feed_types_group() const { return feed_types_group_; }
std::vector<FeedTypesGroup>& FeedTypesGroups::feed_types_group() { return feed_types_group_; }
void FeedTypesGroups::set_feed_types_group(const std::vector<FeedTypesGroup>& value) { feed_types_group_ = value; }

std::size_t FeedTypesGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        feed_types_group_.clear();
        feed_types_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            FeedTypesGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("FeedTypesGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            feed_types_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t FeedTypesGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("FeedTypesGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(feed_types_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(FeedTypesGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : feed_types_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t FeedTypesGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(feed_types_group_);
}

void FeedTypesGroups::print(std::ostream& out) const {
    out << "FeedTypesGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", feed_types_group=";
    print::sequence(out, feed_types_group_);
    out << '}';
}

bool FeedTypesGroups::operator==(const FeedTypesGroups& other) const {
    return group_size_ == other.group_size_
        && feed_types_group_ == other.feed_types_group_;
}

bool FeedTypesGroups::operator!=(const FeedTypesGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const FeedTypesGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
