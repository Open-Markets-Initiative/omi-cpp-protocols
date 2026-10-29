#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/PositionsGroup.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// noPositions Block
class PositionsGroups {
  public:

    PositionsGroups() = default;
    PositionsGroups(const GroupSizeEncoding& group_size_encoding, const std::vector<PositionsGroup>& positions_group);

    // Group Size Encoding: GroupSizeEncoding
    const GroupSizeEncoding& group_size_encoding() const;
    GroupSizeEncoding& group_size_encoding();
    void set_group_size_encoding(const GroupSizeEncoding& value);

    // Positions Group: noPositions
    const std::vector<PositionsGroup>& positions_group() const;
    std::vector<PositionsGroup>& positions_group();
    void set_positions_group(const std::vector<PositionsGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PositionsGroups& other) const;
    bool operator!=(const PositionsGroups& other) const;

  private:
    GroupSizeEncoding group_size_encoding_{};
    std::vector<PositionsGroup> positions_group_{};
};

std::ostream& operator<<(std::ostream& out, const PositionsGroups& value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
