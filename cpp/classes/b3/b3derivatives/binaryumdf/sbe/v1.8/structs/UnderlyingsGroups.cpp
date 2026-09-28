#include "UnderlyingsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

UnderlyingsGroups::UnderlyingsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<UnderlyingsGroup>& underlyings_group)
  : group_size_encoding_(group_size_encoding), underlyings_group_(underlyings_group) {}

const GroupSizeEncoding& UnderlyingsGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& UnderlyingsGroups::group_size_encoding() { return group_size_encoding_; }
void UnderlyingsGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<UnderlyingsGroup>& UnderlyingsGroups::underlyings_group() const { return underlyings_group_; }
std::vector<UnderlyingsGroup>& UnderlyingsGroups::underlyings_group() { return underlyings_group_; }
void UnderlyingsGroups::set_underlyings_group(const std::vector<UnderlyingsGroup>& value) { underlyings_group_ = value; }

std::size_t UnderlyingsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = static_cast<std::size_t>(group_size_encoding_.num_in_group());
        const std::size_t block = static_cast<std::size_t>(group_size_encoding_.block_length());
        underlyings_group_.clear();
        underlyings_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            UnderlyingsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("UnderlyingsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            underlyings_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t UnderlyingsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("UnderlyingsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(underlyings_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(UnderlyingsGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : underlyings_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t UnderlyingsGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(underlyings_group_);
}

void UnderlyingsGroups::print(std::ostream& out) const {
    out << "UnderlyingsGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", underlyings_group=";
    print::sequence(out, underlyings_group_);
    out << '}';
}

bool UnderlyingsGroups::operator==(const UnderlyingsGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && underlyings_group_ == other.underlyings_group_;
}

bool UnderlyingsGroups::operator!=(const UnderlyingsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const UnderlyingsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
