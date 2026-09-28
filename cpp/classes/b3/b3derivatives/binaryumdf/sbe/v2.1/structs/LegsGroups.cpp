#include "LegsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

LegsGroups::LegsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<LegsGroup>& legs_group)
  : group_size_encoding_(group_size_encoding), legs_group_(legs_group) {}

const GroupSizeEncoding& LegsGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& LegsGroups::group_size_encoding() { return group_size_encoding_; }
void LegsGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<LegsGroup>& LegsGroups::legs_group() const { return legs_group_; }
std::vector<LegsGroup>& LegsGroups::legs_group() { return legs_group_; }
void LegsGroups::set_legs_group(const std::vector<LegsGroup>& value) { legs_group_ = value; }

std::size_t LegsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = static_cast<std::size_t>(group_size_encoding_.num_in_group());
        const std::size_t block = static_cast<std::size_t>(group_size_encoding_.block_length());
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
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(legs_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(LegsGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : legs_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t LegsGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(legs_group_);
}

void LegsGroups::print(std::ostream& out) const {
    out << "LegsGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", legs_group=";
    print::sequence(out, legs_group_);
    out << '}';
}

bool LegsGroups::operator==(const LegsGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && legs_group_ == other.legs_group_;
}

bool LegsGroups::operator!=(const LegsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const LegsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
