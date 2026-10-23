#include "SnapshotfullRefreshTcpLongGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

SnapshotfullRefreshTcpLongGroups::SnapshotfullRefreshTcpLongGroups(const GroupSize& group_size, const std::vector<SnapshotfullRefreshTcpLongGroup>& snapshotfull_refresh_tcp_long_group)
  : group_size_(group_size), snapshotfull_refresh_tcp_long_group_(snapshotfull_refresh_tcp_long_group) {}

const GroupSize& SnapshotfullRefreshTcpLongGroups::group_size() const { return group_size_; }
GroupSize& SnapshotfullRefreshTcpLongGroups::group_size() { return group_size_; }
void SnapshotfullRefreshTcpLongGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<SnapshotfullRefreshTcpLongGroup>& SnapshotfullRefreshTcpLongGroups::snapshotfull_refresh_tcp_long_group() const { return snapshotfull_refresh_tcp_long_group_; }
std::vector<SnapshotfullRefreshTcpLongGroup>& SnapshotfullRefreshTcpLongGroups::snapshotfull_refresh_tcp_long_group() { return snapshotfull_refresh_tcp_long_group_; }
void SnapshotfullRefreshTcpLongGroups::set_snapshotfull_refresh_tcp_long_group(const std::vector<SnapshotfullRefreshTcpLongGroup>& value) { snapshotfull_refresh_tcp_long_group_ = value; }

std::size_t SnapshotfullRefreshTcpLongGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        snapshotfull_refresh_tcp_long_group_.clear();
        snapshotfull_refresh_tcp_long_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            SnapshotfullRefreshTcpLongGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("SnapshotfullRefreshTcpLongGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            snapshotfull_refresh_tcp_long_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t SnapshotfullRefreshTcpLongGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SnapshotfullRefreshTcpLongGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(snapshotfull_refresh_tcp_long_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(SnapshotfullRefreshTcpLongGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : snapshotfull_refresh_tcp_long_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t SnapshotfullRefreshTcpLongGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(snapshotfull_refresh_tcp_long_group_);
}

void SnapshotfullRefreshTcpLongGroups::print(std::ostream& out) const {
    out << "SnapshotfullRefreshTcpLongGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", snapshotfull_refresh_tcp_long_group=";
    print::sequence(out, snapshotfull_refresh_tcp_long_group_);
    out << '}';
}

bool SnapshotfullRefreshTcpLongGroups::operator==(const SnapshotfullRefreshTcpLongGroups& other) const {
    return group_size_ == other.group_size_
        && snapshotfull_refresh_tcp_long_group_ == other.snapshotfull_refresh_tcp_long_group_;
}

bool SnapshotfullRefreshTcpLongGroups::operator!=(const SnapshotfullRefreshTcpLongGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const SnapshotfullRefreshTcpLongGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
