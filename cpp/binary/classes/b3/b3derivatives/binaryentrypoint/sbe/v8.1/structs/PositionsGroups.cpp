#include "PositionsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

PositionsGroups::PositionsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<PositionsGroup>& positions_group)
  : group_size_encoding_(group_size_encoding), positions_group_(positions_group) {}

const GroupSizeEncoding& PositionsGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& PositionsGroups::group_size_encoding() { return group_size_encoding_; }
void PositionsGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<PositionsGroup>& PositionsGroups::positions_group() const { return positions_group_; }
std::vector<PositionsGroup>& PositionsGroups::positions_group() { return positions_group_; }
void PositionsGroups::set_positions_group(const std::vector<PositionsGroup>& value) { positions_group_ = value; }

std::size_t PositionsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_encoding_.num_in_group());
        const std::size_t block = wire::count(group_size_encoding_.block_length());
        positions_group_.clear();
        positions_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            PositionsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("PositionsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            positions_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t PositionsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("PositionsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(positions_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(PositionsGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : positions_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t PositionsGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(positions_group_);
}

void PositionsGroups::print(std::ostream& out) const {
    out << "PositionsGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", positions_group=";
    print::sequence(out, positions_group_);
    out << '}';
}

bool PositionsGroups::operator==(const PositionsGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && positions_group_ == other.positions_group_;
}

bool PositionsGroups::operator!=(const PositionsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const PositionsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
