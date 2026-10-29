#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/SidesGroup.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// noSides Block
class SidesGroups {
  public:

    SidesGroups() = default;
    SidesGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<SidesGroup>& sides_group);

    // Group Size Encoding: GroupSizeEncoding
    const GroupSizeEncoding& group_size_encoding() const;
    GroupSizeEncoding& group_size_encoding();
    void set_group_size_encoding(const GroupSizeEncoding& value);

    // Sides Group: noSides
    const std::vector<SidesGroup>& sides_group() const;
    std::vector<SidesGroup>& sides_group();
    void set_sides_group(const std::vector<SidesGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const SidesGroups& other) const;
    bool operator!=(const SidesGroups& other) const;

  private:
    GroupSizeEncoding group_size_encoding_{};
    std::vector<SidesGroup> sides_group_{};
};

std::ostream& operator<<(std::ostream& out, const SidesGroups& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
