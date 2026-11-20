// Cme.Globex.Mdp3.Sbe.v1.9: structs/IncrementalRefreshOrderBookLegacyGroups.cpp
#include "IncrementalRefreshOrderBookLegacyGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

IncrementalRefreshOrderBookLegacyGroups::IncrementalRefreshOrderBookLegacyGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshOrderBookLegacyGroup>& incremental_refresh_order_book_legacy_group)
  : group_size_(group_size), incremental_refresh_order_book_legacy_group_(incremental_refresh_order_book_legacy_group) {}

const GroupSize& IncrementalRefreshOrderBookLegacyGroups::group_size() const { return group_size_; }
GroupSize& IncrementalRefreshOrderBookLegacyGroups::group_size() { return group_size_; }
void IncrementalRefreshOrderBookLegacyGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<IncrementalRefreshOrderBookLegacyGroup>& IncrementalRefreshOrderBookLegacyGroups::incremental_refresh_order_book_legacy_group() const { return incremental_refresh_order_book_legacy_group_; }
std::vector<IncrementalRefreshOrderBookLegacyGroup>& IncrementalRefreshOrderBookLegacyGroups::incremental_refresh_order_book_legacy_group() { return incremental_refresh_order_book_legacy_group_; }
void IncrementalRefreshOrderBookLegacyGroups::set_incremental_refresh_order_book_legacy_group(const std::vector<IncrementalRefreshOrderBookLegacyGroup>& value) { incremental_refresh_order_book_legacy_group_ = value; }

std::size_t IncrementalRefreshOrderBookLegacyGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        incremental_refresh_order_book_legacy_group_.clear();
        incremental_refresh_order_book_legacy_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshOrderBookLegacyGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshOrderBookLegacyGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_order_book_legacy_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshOrderBookLegacyGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshOrderBookLegacyGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_order_book_legacy_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshOrderBookLegacyGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_order_book_legacy_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshOrderBookLegacyGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(incremental_refresh_order_book_legacy_group_);
}

void IncrementalRefreshOrderBookLegacyGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshOrderBookLegacyGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", incremental_refresh_order_book_legacy_group=";
    print::sequence(out, incremental_refresh_order_book_legacy_group_);
    out << '}';
}

bool IncrementalRefreshOrderBookLegacyGroups::operator==(const IncrementalRefreshOrderBookLegacyGroups& other) const {
    return group_size_ == other.group_size_
        && incremental_refresh_order_book_legacy_group_ == other.incremental_refresh_order_book_legacy_group_;
}

bool IncrementalRefreshOrderBookLegacyGroups::operator!=(const IncrementalRefreshOrderBookLegacyGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshOrderBookLegacyGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
