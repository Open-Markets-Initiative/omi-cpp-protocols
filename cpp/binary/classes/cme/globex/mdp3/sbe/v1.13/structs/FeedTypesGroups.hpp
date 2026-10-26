#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/FeedTypesGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

// NoMDFeedTypes Block
class FeedTypesGroups {
  public:

    FeedTypesGroups() = default;
    FeedTypesGroups(const GroupSize& group_size, const std::vector<FeedTypesGroup>& feed_types_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Feed Types Group: Number of repeating FeedType entries
    const std::vector<FeedTypesGroup>& feed_types_group() const;
    std::vector<FeedTypesGroup>& feed_types_group();
    void set_feed_types_group(const std::vector<FeedTypesGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const FeedTypesGroups& other) const;
    bool operator!=(const FeedTypesGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<FeedTypesGroup> feed_types_group_{};
};

std::ostream& operator<<(std::ostream& out, const FeedTypesGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_13
