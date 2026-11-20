// Cme.Globex.Mdp3.Sbe.v1.9: structs/IncrementalRefreshDailyStatisticsLegacyGroups.cpp
#include "IncrementalRefreshDailyStatisticsLegacyGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

IncrementalRefreshDailyStatisticsLegacyGroups::IncrementalRefreshDailyStatisticsLegacyGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshDailyStatisticsLegacyGroup>& incremental_refresh_daily_statistics_legacy_group)
  : group_size_(group_size), incremental_refresh_daily_statistics_legacy_group_(incremental_refresh_daily_statistics_legacy_group) {}

const GroupSize& IncrementalRefreshDailyStatisticsLegacyGroups::group_size() const { return group_size_; }
GroupSize& IncrementalRefreshDailyStatisticsLegacyGroups::group_size() { return group_size_; }
void IncrementalRefreshDailyStatisticsLegacyGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<IncrementalRefreshDailyStatisticsLegacyGroup>& IncrementalRefreshDailyStatisticsLegacyGroups::incremental_refresh_daily_statistics_legacy_group() const { return incremental_refresh_daily_statistics_legacy_group_; }
std::vector<IncrementalRefreshDailyStatisticsLegacyGroup>& IncrementalRefreshDailyStatisticsLegacyGroups::incremental_refresh_daily_statistics_legacy_group() { return incremental_refresh_daily_statistics_legacy_group_; }
void IncrementalRefreshDailyStatisticsLegacyGroups::set_incremental_refresh_daily_statistics_legacy_group(const std::vector<IncrementalRefreshDailyStatisticsLegacyGroup>& value) { incremental_refresh_daily_statistics_legacy_group_ = value; }

std::size_t IncrementalRefreshDailyStatisticsLegacyGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        incremental_refresh_daily_statistics_legacy_group_.clear();
        incremental_refresh_daily_statistics_legacy_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshDailyStatisticsLegacyGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshDailyStatisticsLegacyGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_daily_statistics_legacy_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshDailyStatisticsLegacyGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshDailyStatisticsLegacyGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_daily_statistics_legacy_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshDailyStatisticsLegacyGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_daily_statistics_legacy_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshDailyStatisticsLegacyGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(incremental_refresh_daily_statistics_legacy_group_);
}

void IncrementalRefreshDailyStatisticsLegacyGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshDailyStatisticsLegacyGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", incremental_refresh_daily_statistics_legacy_group=";
    print::sequence(out, incremental_refresh_daily_statistics_legacy_group_);
    out << '}';
}

bool IncrementalRefreshDailyStatisticsLegacyGroups::operator==(const IncrementalRefreshDailyStatisticsLegacyGroups& other) const {
    return group_size_ == other.group_size_
        && incremental_refresh_daily_statistics_legacy_group_ == other.incremental_refresh_daily_statistics_legacy_group_;
}

bool IncrementalRefreshDailyStatisticsLegacyGroups::operator!=(const IncrementalRefreshDailyStatisticsLegacyGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshDailyStatisticsLegacyGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_9
