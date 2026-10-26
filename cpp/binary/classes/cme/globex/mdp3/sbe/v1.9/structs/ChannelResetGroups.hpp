#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/ChannelResetGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

// NoMDEntries Block
class ChannelResetGroups {
  public:

    ChannelResetGroups() = default;
    ChannelResetGroups(const GroupSize& group_size, const std::vector<ChannelResetGroup>& channel_reset_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Channel Reset Group: Number of entries in Market Data message
    const std::vector<ChannelResetGroup>& channel_reset_group() const;
    std::vector<ChannelResetGroup>& channel_reset_group();
    void set_channel_reset_group(const std::vector<ChannelResetGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const ChannelResetGroups& other) const;
    bool operator!=(const ChannelResetGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<ChannelResetGroup> channel_reset_group_{};
};

std::ostream& operator<<(std::ostream& out, const ChannelResetGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_9
