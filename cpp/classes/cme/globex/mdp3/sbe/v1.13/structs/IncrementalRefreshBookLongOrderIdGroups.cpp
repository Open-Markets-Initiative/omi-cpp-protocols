#include "IncrementalRefreshBookLongOrderIdGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshBookLongOrderIdGroups::IncrementalRefreshBookLongOrderIdGroups(const GroupSize8Byte& group_size_8_byte, const std::vector<IncrementalRefreshBookLongOrderIdGroup>& incremental_refresh_book_long_order_id_group)
  : group_size_8_byte_(group_size_8_byte), incremental_refresh_book_long_order_id_group_(incremental_refresh_book_long_order_id_group) {}

const GroupSize8Byte& IncrementalRefreshBookLongOrderIdGroups::group_size_8_byte() const { return group_size_8_byte_; }
GroupSize8Byte& IncrementalRefreshBookLongOrderIdGroups::group_size_8_byte() { return group_size_8_byte_; }
void IncrementalRefreshBookLongOrderIdGroups::set_group_size_8_byte(const GroupSize8Byte& value) { group_size_8_byte_ = value; }

const std::vector<IncrementalRefreshBookLongOrderIdGroup>& IncrementalRefreshBookLongOrderIdGroups::incremental_refresh_book_long_order_id_group() const { return incremental_refresh_book_long_order_id_group_; }
std::vector<IncrementalRefreshBookLongOrderIdGroup>& IncrementalRefreshBookLongOrderIdGroups::incremental_refresh_book_long_order_id_group() { return incremental_refresh_book_long_order_id_group_; }
void IncrementalRefreshBookLongOrderIdGroups::set_incremental_refresh_book_long_order_id_group(const std::vector<IncrementalRefreshBookLongOrderIdGroup>& value) { incremental_refresh_book_long_order_id_group_ = value; }

std::size_t IncrementalRefreshBookLongOrderIdGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_8_byte_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_8_byte_.num_in_group());
        const std::size_t block = wire::count(group_size_8_byte_.block_length());
        incremental_refresh_book_long_order_id_group_.clear();
        incremental_refresh_book_long_order_id_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshBookLongOrderIdGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshBookLongOrderIdGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_book_long_order_id_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshBookLongOrderIdGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshBookLongOrderIdGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_8_byte = group_size_8_byte_;
    group_size_8_byte.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_book_long_order_id_group_.size()));
    group_size_8_byte.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshBookLongOrderIdGroup::wire_size));

    offset += group_size_8_byte.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_book_long_order_id_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshBookLongOrderIdGroups::encoded_size() const {
    return group_size_8_byte_.encoded_size() + wire::encoded_size_of(incremental_refresh_book_long_order_id_group_);
}

void IncrementalRefreshBookLongOrderIdGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshBookLongOrderIdGroups{";
    out << "group_size_8_byte=";
    group_size_8_byte_.print(out);
    out << ", incremental_refresh_book_long_order_id_group=";
    print::sequence(out, incremental_refresh_book_long_order_id_group_);
    out << '}';
}

bool IncrementalRefreshBookLongOrderIdGroups::operator==(const IncrementalRefreshBookLongOrderIdGroups& other) const {
    return group_size_8_byte_ == other.group_size_8_byte_
        && incremental_refresh_book_long_order_id_group_ == other.incremental_refresh_book_long_order_id_group_;
}

bool IncrementalRefreshBookLongOrderIdGroups::operator!=(const IncrementalRefreshBookLongOrderIdGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshBookLongOrderIdGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
