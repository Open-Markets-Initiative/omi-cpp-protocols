#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/LegacyLegsGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// NoLegs Block
class LegacyLegsGroups {
  public:

    LegacyLegsGroups() = default;
    LegacyLegsGroups(const GroupSize& group_size, const std::vector<LegacyLegsGroup>& legacy_legs_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Legacy Legs Group: Number of Leg entries
    const std::vector<LegacyLegsGroup>& legacy_legs_group() const;
    std::vector<LegacyLegsGroup>& legacy_legs_group();
    void set_legacy_legs_group(const std::vector<LegacyLegsGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const LegacyLegsGroups& other) const;
    bool operator!=(const LegacyLegsGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<LegacyLegsGroup> legacy_legs_group_{};
};

std::ostream& operator<<(std::ostream& out, const LegacyLegsGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_5
