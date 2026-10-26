#include "IncrementalRefreshTradeSummaryGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

IncrementalRefreshTradeSummaryGroups::IncrementalRefreshTradeSummaryGroups(const GroupSize& group_size, const std::vector<IncrementalRefreshTradeSummaryGroup>& incremental_refresh_trade_summary_group)
  : group_size_(group_size), incremental_refresh_trade_summary_group_(incremental_refresh_trade_summary_group) {}

const GroupSize& IncrementalRefreshTradeSummaryGroups::group_size() const { return group_size_; }
GroupSize& IncrementalRefreshTradeSummaryGroups::group_size() { return group_size_; }
void IncrementalRefreshTradeSummaryGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<IncrementalRefreshTradeSummaryGroup>& IncrementalRefreshTradeSummaryGroups::incremental_refresh_trade_summary_group() const { return incremental_refresh_trade_summary_group_; }
std::vector<IncrementalRefreshTradeSummaryGroup>& IncrementalRefreshTradeSummaryGroups::incremental_refresh_trade_summary_group() { return incremental_refresh_trade_summary_group_; }
void IncrementalRefreshTradeSummaryGroups::set_incremental_refresh_trade_summary_group(const std::vector<IncrementalRefreshTradeSummaryGroup>& value) { incremental_refresh_trade_summary_group_ = value; }

std::size_t IncrementalRefreshTradeSummaryGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        incremental_refresh_trade_summary_group_.clear();
        incremental_refresh_trade_summary_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshTradeSummaryGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshTradeSummaryGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_trade_summary_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshTradeSummaryGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_trade_summary_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshTradeSummaryGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_trade_summary_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(incremental_refresh_trade_summary_group_);
}

void IncrementalRefreshTradeSummaryGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshTradeSummaryGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", incremental_refresh_trade_summary_group=";
    print::sequence(out, incremental_refresh_trade_summary_group_);
    out << '}';
}

bool IncrementalRefreshTradeSummaryGroups::operator==(const IncrementalRefreshTradeSummaryGroups& other) const {
    return group_size_ == other.group_size_
        && incremental_refresh_trade_summary_group_ == other.incremental_refresh_trade_summary_group_;
}

bool IncrementalRefreshTradeSummaryGroups::operator!=(const IncrementalRefreshTradeSummaryGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_8
