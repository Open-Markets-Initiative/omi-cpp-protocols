#include "GroupSize8Byte.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

GroupSize8Byte::GroupSize8Byte(std::uint16_t block_length, const std::array<std::byte, 5>& padding_5, std::uint8_t num_in_group)
  : block_length_(block_length), padding_5_(padding_5), num_in_group_(num_in_group) {}

std::uint16_t GroupSize8Byte::block_length() const { return block_length_; }
void GroupSize8Byte::set_block_length(std::uint16_t value) { block_length_ = value; }

const std::array<std::byte, 5>& GroupSize8Byte::padding_5() const { return padding_5_; }
std::array<std::byte, 5>& GroupSize8Byte::padding_5() { return padding_5_; }
void GroupSize8Byte::set_padding_5(const std::array<std::byte, 5>& value) { padding_5_ = value; }

std::uint8_t GroupSize8Byte::num_in_group() const { return num_in_group_; }
void GroupSize8Byte::set_num_in_group(std::uint8_t value) { num_in_group_ = value; }

std::size_t GroupSize8Byte::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("GroupSize8Byte", wire_size, length);

    block_length_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::read_bytes(data + offset, padding_5_.data(), 5);
    offset += 5;

    num_in_group_ = wire::read_u8(data + offset);
    offset += 1;

    return offset;
}

std::size_t GroupSize8Byte::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("GroupSize8Byte", wire_size, capacity);

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(block_length_));
    offset += 2;

    wire::write_bytes(data + offset, padding_5_.data(), 5);
    offset += 5;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(num_in_group_));
    offset += 1;

    return offset;
}

std::size_t GroupSize8Byte::encoded_size() const {
    return wire_size;
}

void GroupSize8Byte::print(std::ostream& out) const {
    out << "GroupSize8Byte{";
    out << "block_length=";
    out << block_length_;
    out << ", padding_5=";
    print::hex(out, padding_5_.data(), padding_5_.size());
    out << ", num_in_group=";
    out << static_cast<int>(num_in_group_);
    out << '}';
}

bool GroupSize8Byte::operator==(const GroupSize8Byte& other) const {
    return block_length_ == other.block_length_
        && padding_5_ == other.padding_5_
        && num_in_group_ == other.num_in_group_;
}

bool GroupSize8Byte::operator!=(const GroupSize8Byte& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const GroupSize8Byte& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
