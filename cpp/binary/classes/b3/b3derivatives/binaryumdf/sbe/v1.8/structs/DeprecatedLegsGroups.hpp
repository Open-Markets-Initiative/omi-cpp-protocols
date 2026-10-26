#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/DeprecatedLegsGroup.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// noLegs Block
class DeprecatedLegsGroups {
  public:

    DeprecatedLegsGroups() = default;
    DeprecatedLegsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<DeprecatedLegsGroup>& deprecated_legs_group);

    // Group Size Encoding: GroupSizeEncoding
    const GroupSizeEncoding& group_size_encoding() const;
    GroupSizeEncoding& group_size_encoding();
    void set_group_size_encoding(const GroupSizeEncoding& value);

    // Deprecated Legs Group: noLegs
    const std::vector<DeprecatedLegsGroup>& deprecated_legs_group() const;
    std::vector<DeprecatedLegsGroup>& deprecated_legs_group();
    void set_deprecated_legs_group(const std::vector<DeprecatedLegsGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const DeprecatedLegsGroups& other) const;
    bool operator!=(const DeprecatedLegsGroups& other) const;

  private:
    GroupSizeEncoding group_size_encoding_{};
    std::vector<DeprecatedLegsGroup> deprecated_legs_group_{};
};

std::ostream& operator<<(std::ostream& out, const DeprecatedLegsGroups& value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
