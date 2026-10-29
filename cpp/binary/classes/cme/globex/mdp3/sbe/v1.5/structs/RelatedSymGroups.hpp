#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/RelatedSymGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

// NoRelatedSym Block
class RelatedSymGroups {
  public:

    RelatedSymGroups() = default;
    RelatedSymGroups(const GroupSize& group_size, const std::vector<RelatedSymGroup>& related_sym_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Related Sym Group: Indicates the number of repeating symbols specified
    const std::vector<RelatedSymGroup>& related_sym_group() const;
    std::vector<RelatedSymGroup>& related_sym_group();
    void set_related_sym_group(const std::vector<RelatedSymGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RelatedSymGroups& other) const;
    bool operator!=(const RelatedSymGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<RelatedSymGroup> related_sym_group_{};
};

std::ostream& operator<<(std::ostream& out, const RelatedSymGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_5
