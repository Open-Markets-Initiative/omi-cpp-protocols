#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/RepoUnderlyingsGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoUnderlyings Block
class RepoUnderlyingsGroups {
  public:

    RepoUnderlyingsGroups() = default;
    RepoUnderlyingsGroups(const GroupSize& group_size, const std::vector<RepoUnderlyingsGroup>& repo_underlyings_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Repo Underlyings Group: Number of underlying entries
    const std::vector<RepoUnderlyingsGroup>& repo_underlyings_group() const;
    std::vector<RepoUnderlyingsGroup>& repo_underlyings_group();
    void set_repo_underlyings_group(const std::vector<RepoUnderlyingsGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const RepoUnderlyingsGroups& other) const;
    bool operator!=(const RepoUnderlyingsGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<RepoUnderlyingsGroup> repo_underlyings_group_{};
};

std::ostream& operator<<(std::ostream& out, const RepoUnderlyingsGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
