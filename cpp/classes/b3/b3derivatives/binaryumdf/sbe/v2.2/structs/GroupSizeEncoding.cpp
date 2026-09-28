#include "GroupSizeEncoding.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

GroupSizeEncoding::GroupSizeEncoding(std::uint16_t block_length, std::uint8_t num_in_group)
  : block_length_(block_length), num_in_group_(num_in_group) {}

std::uint16_t GroupSizeEncoding::block_length() const { return block_length_; }
void GroupSizeEncoding::set_block_length(std::uint16_t value) { block_length_ = value; }

std::uint8_t GroupSizeEncoding::num_in_group() const { return num_in_group_; }
void GroupSizeEncoding::set_num_in_group(std::uint8_t value) { num_in_group_ = value; }

std::size_t GroupSizeEncoding::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("GroupSizeEncoding", wire_size, length);

    block_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    num_in_group_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t GroupSizeEncoding::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("GroupSizeEncoding", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(block_length_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_in_group_));
    offset += 1;

    return offset;
}

std::size_t GroupSizeEncoding::encoded_size() const {
    return wire_size;
}

void GroupSizeEncoding::print(std::ostream& out) const {
    out << "GroupSizeEncoding{";
    out << "block_length=";
    out << block_length_;
    out << ", num_in_group=";
    out << static_cast<int>(num_in_group_);
    out << '}';
}

bool GroupSizeEncoding::operator==(const GroupSizeEncoding& other) const {
    return block_length_ == other.block_length_
        && num_in_group_ == other.num_in_group_;
}

bool GroupSizeEncoding::operator!=(const GroupSizeEncoding& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const GroupSizeEncoding& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
