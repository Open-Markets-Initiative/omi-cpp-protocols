#include "InstrAttribsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

InstrAttribsGroups::InstrAttribsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<InstrAttribsGroup>& instr_attribs_group)
  : group_size_encoding_(group_size_encoding), instr_attribs_group_(instr_attribs_group) {}

const GroupSizeEncoding& InstrAttribsGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& InstrAttribsGroups::group_size_encoding() { return group_size_encoding_; }
void InstrAttribsGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<InstrAttribsGroup>& InstrAttribsGroups::instr_attribs_group() const { return instr_attribs_group_; }
std::vector<InstrAttribsGroup>& InstrAttribsGroups::instr_attribs_group() { return instr_attribs_group_; }
void InstrAttribsGroups::set_instr_attribs_group(const std::vector<InstrAttribsGroup>& value) { instr_attribs_group_ = value; }

std::size_t InstrAttribsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = static_cast<std::size_t>(group_size_encoding_.num_in_group());
        const std::size_t block = static_cast<std::size_t>(group_size_encoding_.block_length());
        instr_attribs_group_.clear();
        instr_attribs_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            InstrAttribsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("InstrAttribsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            instr_attribs_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t InstrAttribsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrAttribsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(instr_attribs_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(InstrAttribsGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : instr_attribs_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t InstrAttribsGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(instr_attribs_group_);
}

void InstrAttribsGroups::print(std::ostream& out) const {
    out << "InstrAttribsGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", instr_attribs_group=";
    print::sequence(out, instr_attribs_group_);
    out << '}';
}

bool InstrAttribsGroups::operator==(const InstrAttribsGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && instr_attribs_group_ == other.instr_attribs_group_;
}

bool InstrAttribsGroups::operator!=(const InstrAttribsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const InstrAttribsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
