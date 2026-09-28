#include "DeprecatedLegsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

DeprecatedLegsGroups::DeprecatedLegsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<DeprecatedLegsGroup>& deprecated_legs_group)
  : group_size_encoding_(group_size_encoding), deprecated_legs_group_(deprecated_legs_group) {}

const GroupSizeEncoding& DeprecatedLegsGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& DeprecatedLegsGroups::group_size_encoding() { return group_size_encoding_; }
void DeprecatedLegsGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<DeprecatedLegsGroup>& DeprecatedLegsGroups::deprecated_legs_group() const { return deprecated_legs_group_; }
std::vector<DeprecatedLegsGroup>& DeprecatedLegsGroups::deprecated_legs_group() { return deprecated_legs_group_; }
void DeprecatedLegsGroups::set_deprecated_legs_group(const std::vector<DeprecatedLegsGroup>& value) { deprecated_legs_group_ = value; }

std::size_t DeprecatedLegsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = static_cast<std::size_t>(group_size_encoding_.num_in_group());
        const std::size_t block = static_cast<std::size_t>(group_size_encoding_.block_length());
        deprecated_legs_group_.clear();
        deprecated_legs_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            DeprecatedLegsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("DeprecatedLegsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            deprecated_legs_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t DeprecatedLegsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeprecatedLegsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(deprecated_legs_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(DeprecatedLegsGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : deprecated_legs_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t DeprecatedLegsGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(deprecated_legs_group_);
}

void DeprecatedLegsGroups::print(std::ostream& out) const {
    out << "DeprecatedLegsGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", deprecated_legs_group=";
    print::sequence(out, deprecated_legs_group_);
    out << '}';
}

bool DeprecatedLegsGroups::operator==(const DeprecatedLegsGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && deprecated_legs_group_ == other.deprecated_legs_group_;
}

bool DeprecatedLegsGroups::operator!=(const DeprecatedLegsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const DeprecatedLegsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
