#include "DeprecatedInstrAttribsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

DeprecatedInstrAttribsGroups::DeprecatedInstrAttribsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<DeprecatedInstrAttribsGroup>& deprecated_instr_attribs_group)
  : group_size_encoding_(group_size_encoding), deprecated_instr_attribs_group_(deprecated_instr_attribs_group) {}

const GroupSizeEncoding& DeprecatedInstrAttribsGroups::group_size_encoding() const { return group_size_encoding_; }
GroupSizeEncoding& DeprecatedInstrAttribsGroups::group_size_encoding() { return group_size_encoding_; }
void DeprecatedInstrAttribsGroups::set_group_size_encoding(const GroupSizeEncoding& value) { group_size_encoding_ = value; }

const std::vector<DeprecatedInstrAttribsGroup>& DeprecatedInstrAttribsGroups::deprecated_instr_attribs_group() const { return deprecated_instr_attribs_group_; }
std::vector<DeprecatedInstrAttribsGroup>& DeprecatedInstrAttribsGroups::deprecated_instr_attribs_group() { return deprecated_instr_attribs_group_; }
void DeprecatedInstrAttribsGroups::set_deprecated_instr_attribs_group(const std::vector<DeprecatedInstrAttribsGroup>& value) { deprecated_instr_attribs_group_ = value; }

std::size_t DeprecatedInstrAttribsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_encoding_.decode(data + offset, length - offset);

    {
        const std::size_t count = static_cast<std::size_t>(group_size_encoding_.num_in_group());
        const std::size_t block = static_cast<std::size_t>(group_size_encoding_.block_length());
        deprecated_instr_attribs_group_.clear();
        deprecated_instr_attribs_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            DeprecatedInstrAttribsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("DeprecatedInstrAttribsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            deprecated_instr_attribs_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t DeprecatedInstrAttribsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("DeprecatedInstrAttribsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_encoding = group_size_encoding_;
    group_size_encoding.set_num_in_group(static_cast<std::uint8_t>(deprecated_instr_attribs_group_.size()));
    group_size_encoding.set_block_length(static_cast<std::uint16_t>(DeprecatedInstrAttribsGroup::wire_size));

    offset += group_size_encoding.encode(data + offset, capacity - offset);

    for (const auto& entry : deprecated_instr_attribs_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t DeprecatedInstrAttribsGroups::encoded_size() const {
    return group_size_encoding_.encoded_size() + wire::encoded_size_of(deprecated_instr_attribs_group_);
}

void DeprecatedInstrAttribsGroups::print(std::ostream& out) const {
    out << "DeprecatedInstrAttribsGroups{";
    out << "group_size_encoding=";
    group_size_encoding_.print(out);
    out << ", deprecated_instr_attribs_group=";
    print::sequence(out, deprecated_instr_attribs_group_);
    out << '}';
}

bool DeprecatedInstrAttribsGroups::operator==(const DeprecatedInstrAttribsGroups& other) const {
    return group_size_encoding_ == other.group_size_encoding_
        && deprecated_instr_attribs_group_ == other.deprecated_instr_attribs_group_;
}

bool DeprecatedInstrAttribsGroups::operator!=(const DeprecatedInstrAttribsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const DeprecatedInstrAttribsGroups& value) {
    value.print(out);
    return out;
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
