#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/InstrAttribsGroup.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// noInstrAttribs Block
class InstrAttribsGroups {
  public:

    InstrAttribsGroups() = default;
    InstrAttribsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<InstrAttribsGroup>& instr_attribs_group);

    // Group Size Encoding: GroupSizeEncoding
    const GroupSizeEncoding& group_size_encoding() const;
    GroupSizeEncoding& group_size_encoding();
    void set_group_size_encoding(const GroupSizeEncoding& value);

    // Instr Attribs Group: noInstrAttribs
    const std::vector<InstrAttribsGroup>& instr_attribs_group() const;
    std::vector<InstrAttribsGroup>& instr_attribs_group();
    void set_instr_attribs_group(const std::vector<InstrAttribsGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstrAttribsGroups& other) const;
    bool operator!=(const InstrAttribsGroups& other) const;

  private:
    GroupSizeEncoding group_size_encoding_{};
    std::vector<InstrAttribsGroup> instr_attribs_group_{};
};

std::ostream& operator<<(std::ostream& out, const InstrAttribsGroups& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
