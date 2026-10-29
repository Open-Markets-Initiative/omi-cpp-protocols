#include "CrossSidesGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

CrossSidesGroups::CrossSidesGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<CrossSidesGroup>& cross_sides_group)
  : group_size_encoding_(group_size_encoding), cross_sides_group_(cross_sides_group) {}

const GroupSizeEncoding& CrossSidesGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& CrossSidesGroups::group_size_encoding() { return group_size_encoding_; }
void CrossSidesGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<CrossSidesGroup>& CrossSidesGroups::cross_sides_group() const { return cross_sides_group_; }
std::vector<CrossSidesGroup>& CrossSidesGroups::cross_sides_group() { return cross_sides_group_; }
void CrossSidesGroups::set_cross_sides_group(const std::vector<CrossSidesGroup>& value) { cross_sides_group_ = value; }

std::size_t CrossSidesGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_encoding_.num_in_group());
        const std::size_t block = wire::count(group_size_encoding_.block_length());
        cross_sides_group_.clear();
        cross_sides_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            CrossSidesGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("CrossSidesGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            cross_sides_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t CrossSidesGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CrossSidesGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(cross_sides_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(CrossSidesGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : cross_sides_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t CrossSidesGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(cross_sides_group_);
}

void CrossSidesGroups::print(std::ostream& out) const {
    out << "CrossSidesGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", cross_sides_group=";
    print::sequence(out, cross_sides_group_);
    out << '}';
}

bool CrossSidesGroups::operator==(const CrossSidesGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && cross_sides_group_ == other.cross_sides_group_;
}

bool CrossSidesGroups::operator!=(const CrossSidesGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CrossSidesGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
