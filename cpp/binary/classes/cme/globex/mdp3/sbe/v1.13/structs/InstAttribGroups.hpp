#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/InstAttribGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoInstAttrib Block
class InstAttribGroups {
  public:

    InstAttribGroups() = default;
    InstAttribGroups(const GroupSize& group_size, const std::vector<InstAttribGroup>& inst_attrib_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Inst Attrib Group: Number of repeating InstrAttribType entries
    const std::vector<InstAttribGroup>& inst_attrib_group() const;
    std::vector<InstAttribGroup>& inst_attrib_group();
    void set_inst_attrib_group(const std::vector<InstAttribGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const InstAttribGroups& other) const;
    bool operator!=(const InstAttribGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<InstAttribGroup> inst_attrib_group_{};
};

std::ostream& operator<<(std::ostream& out, const InstAttribGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
