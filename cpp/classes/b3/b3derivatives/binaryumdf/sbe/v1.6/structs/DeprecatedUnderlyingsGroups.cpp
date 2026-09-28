#include "DeprecatedUnderlyingsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

DeprecatedUnderlyingsGroups::DeprecatedUnderlyingsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<DeprecatedUnderlyingsGroup>& deprecated_underlyings_group)
  : group_size_encoding_(group_size_encoding), deprecated_underlyings_group_(deprecated_underlyings_group) {}

const GroupSizeEncoding& DeprecatedUnderlyingsGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& DeprecatedUnderlyingsGroups::group_size_encoding() { return group_size_encoding_; }
void DeprecatedUnderlyingsGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<DeprecatedUnderlyingsGroup>& DeprecatedUnderlyingsGroups::deprecated_underlyings_group() const { return deprecated_underlyings_group_; }
std::vector<DeprecatedUnderlyingsGroup>& DeprecatedUnderlyingsGroups::deprecated_underlyings_group() { return deprecated_underlyings_group_; }
void DeprecatedUnderlyingsGroups::set_deprecated_underlyings_group(const std::vector<DeprecatedUnderlyingsGroup>& value) { deprecated_underlyings_group_ = value; }

std::size_t DeprecatedUnderlyingsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = static_cast<std::size_t>(group_size_encoding_.num_in_group());
        const std::size_t block = static_cast<std::size_t>(group_size_encoding_.block_length());
        deprecated_underlyings_group_.clear();
        deprecated_underlyings_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            DeprecatedUnderlyingsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("DeprecatedUnderlyingsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            deprecated_underlyings_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t DeprecatedUnderlyingsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeprecatedUnderlyingsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(deprecated_underlyings_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(DeprecatedUnderlyingsGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : deprecated_underlyings_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t DeprecatedUnderlyingsGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(deprecated_underlyings_group_);
}

void DeprecatedUnderlyingsGroups::print(std::ostream& out) const {
    out << "DeprecatedUnderlyingsGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", deprecated_underlyings_group=";
    print::sequence(out, deprecated_underlyings_group_);
    out << '}';
}

bool DeprecatedUnderlyingsGroups::operator==(const DeprecatedUnderlyingsGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && deprecated_underlyings_group_ == other.deprecated_underlyings_group_;
}

bool DeprecatedUnderlyingsGroups::operator!=(const DeprecatedUnderlyingsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const DeprecatedUnderlyingsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
