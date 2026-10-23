#include "ChannelResetGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ChannelResetGroups::ChannelResetGroups(const GroupSize& group_size, const std::vector<ChannelResetGroup>& channel_reset_group)
  : group_size_(group_size), channel_reset_group_(channel_reset_group) {}

const GroupSize& ChannelResetGroups::group_size() const { return group_size_; }
GroupSize& ChannelResetGroups::group_size() { return group_size_; }
void ChannelResetGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<ChannelResetGroup>& ChannelResetGroups::channel_reset_group() const { return channel_reset_group_; }
std::vector<ChannelResetGroup>& ChannelResetGroups::channel_reset_group() { return channel_reset_group_; }
void ChannelResetGroups::set_channel_reset_group(const std::vector<ChannelResetGroup>& value) { channel_reset_group_ = value; }

std::size_t ChannelResetGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        channel_reset_group_.clear();
        channel_reset_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            ChannelResetGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("ChannelResetGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            channel_reset_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t ChannelResetGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ChannelResetGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(channel_reset_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(ChannelResetGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : channel_reset_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t ChannelResetGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(channel_reset_group_);
}

void ChannelResetGroups::print(std::ostream& out) const {
    out << "ChannelResetGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", channel_reset_group=";
    print::sequence(out, channel_reset_group_);
    out << '}';
}

bool ChannelResetGroups::operator==(const ChannelResetGroups& other) const {
    return group_size_ == other.group_size_
        && channel_reset_group_ == other.channel_reset_group_;
}

bool ChannelResetGroups::operator!=(const ChannelResetGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const ChannelResetGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
