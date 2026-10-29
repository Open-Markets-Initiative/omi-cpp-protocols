#include "SidesGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

SidesGroups::SidesGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<SidesGroup>& sides_group)
  : group_size_encoding_(group_size_encoding), sides_group_(sides_group) {}

const GroupSizeEncoding& SidesGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& SidesGroups::group_size_encoding() { return group_size_encoding_; }
void SidesGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<SidesGroup>& SidesGroups::sides_group() const { return sides_group_; }
std::vector<SidesGroup>& SidesGroups::sides_group() { return sides_group_; }
void SidesGroups::set_sides_group(const std::vector<SidesGroup>& value) { sides_group_ = value; }

std::size_t SidesGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_encoding_.num_in_group());
        const std::size_t block = wire::count(group_size_encoding_.block_length());
        sides_group_.clear();
        sides_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SidesGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SidesGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            sides_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SidesGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SidesGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(sides_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(SidesGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : sides_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SidesGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(sides_group_);
}

void SidesGroups::print(std::ostream& out) const {
    out << "SidesGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", sides_group=";
    print::sequence(out, sides_group_);
    out << '}';
}

bool SidesGroups::operator==(const SidesGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && sides_group_ == other.sides_group_;
}

bool SidesGroups::operator!=(const SidesGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SidesGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
