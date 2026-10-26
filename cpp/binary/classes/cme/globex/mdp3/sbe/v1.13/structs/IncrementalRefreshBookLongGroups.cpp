#include "IncrementalRefreshBookLongGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshBookLongGroups::IncrementalRefreshBookLongGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshBookLongGroup>& incremental_refresh_book_long_group)
  : group_size_(group_size), incremental_refresh_book_long_group_(incremental_refresh_book_long_group) {}

const GroupSize& IncrementalRefreshBookLongGroups::group_size() const { return group_size_; }
GroupSize& IncrementalRefreshBookLongGroups::group_size() { return group_size_; }
void IncrementalRefreshBookLongGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<IncrementalRefreshBookLongGroup>& IncrementalRefreshBookLongGroups::incremental_refresh_book_long_group() const { return incremental_refresh_book_long_group_; }
std::vector<IncrementalRefreshBookLongGroup>& IncrementalRefreshBookLongGroups::incremental_refresh_book_long_group() { return incremental_refresh_book_long_group_; }
void IncrementalRefreshBookLongGroups::set_incremental_refresh_book_long_group(const std::vector<IncrementalRefreshBookLongGroup>& value) { incremental_refresh_book_long_group_ = value; }

std::size_t IncrementalRefreshBookLongGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        incremental_refresh_book_long_group_.clear();
        incremental_refresh_book_long_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshBookLongGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshBookLongGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_book_long_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshBookLongGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshBookLongGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_book_long_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshBookLongGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_book_long_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshBookLongGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(incremental_refresh_book_long_group_);
}

void IncrementalRefreshBookLongGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshBookLongGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", incremental_refresh_book_long_group=";
    print::sequence(out, incremental_refresh_book_long_group_);
    out << '}';
}

bool IncrementalRefreshBookLongGroups::operator==(const IncrementalRefreshBookLongGroups& other) const {
    return group_size_ == other.group_size_
        && incremental_refresh_book_long_group_ == other.incremental_refresh_book_long_group_;
}

bool IncrementalRefreshBookLongGroups::operator!=(const IncrementalRefreshBookLongGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookLongGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
