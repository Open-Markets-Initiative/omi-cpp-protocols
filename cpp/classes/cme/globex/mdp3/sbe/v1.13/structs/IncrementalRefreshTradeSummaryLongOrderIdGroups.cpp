#include "IncrementalRefreshTradeSummaryLongOrderIdGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

IncrementalRefreshTradeSummaryLongOrderIdGroups::IncrementalRefreshTradeSummaryLongOrderIdGroups(const GroupSize8Byte& group_size_8_byte, const std::vector<IncrementalRefreshTradeSummaryLongOrderIdGroup>& incremental_refresh_trade_summary_long_order_id_group)
  : group_size_8_byte_(group_size_8_byte), incremental_refresh_trade_summary_long_order_id_group_(incremental_refresh_trade_summary_long_order_id_group) {}

const GroupSize8Byte& IncrementalRefreshTradeSummaryLongOrderIdGroups::group_size_8_byte() const { return group_size_8_byte_; }
GroupSize8Byte& IncrementalRefreshTradeSummaryLongOrderIdGroups::group_size_8_byte() { return group_size_8_byte_; }
void IncrementalRefreshTradeSummaryLongOrderIdGroups::set_group_size_8_byte(const GroupSize8Byte& value) { group_size_8_byte_ = value; }

const std::vector<IncrementalRefreshTradeSummaryLongOrderIdGroup>& IncrementalRefreshTradeSummaryLongOrderIdGroups::incremental_refresh_trade_summary_long_order_id_group() const { return incremental_refresh_trade_summary_long_order_id_group_; }
std::vector<IncrementalRefreshTradeSummaryLongOrderIdGroup>& IncrementalRefreshTradeSummaryLongOrderIdGroups::incremental_refresh_trade_summary_long_order_id_group() { return incremental_refresh_trade_summary_long_order_id_group_; }
void IncrementalRefreshTradeSummaryLongOrderIdGroups::set_incremental_refresh_trade_summary_long_order_id_group(const std::vector<IncrementalRefreshTradeSummaryLongOrderIdGroup>& value) { incremental_refresh_trade_summary_long_order_id_group_ = value; }

std::size_t IncrementalRefreshTradeSummaryLongOrderIdGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_8_byte_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_8_byte_.num_in_group());
        const std::size_t block = wire::count(group_size_8_byte_.block_length());
        incremental_refresh_trade_summary_long_order_id_group_.clear();
        incremental_refresh_trade_summary_long_order_id_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            IncrementalRefreshTradeSummaryLongOrderIdGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("IncrementalRefreshTradeSummaryLongOrderIdGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            incremental_refresh_trade_summary_long_order_id_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryLongOrderIdGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("IncrementalRefreshTradeSummaryLongOrderIdGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size_8_byte = group_size_8_byte_;
    group_size_8_byte.set_num_in_group(static_cast<std::uint8_t>(incremental_refresh_trade_summary_long_order_id_group_.size()));
    group_size_8_byte.set_block_length(static_cast<std::uint16_t>(IncrementalRefreshTradeSummaryLongOrderIdGroup::wire_size));

    offset += group_size_8_byte.encode(data + offset, capacity - offset);

    for (const auto& entry : incremental_refresh_trade_summary_long_order_id_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t IncrementalRefreshTradeSummaryLongOrderIdGroups::encoded_size() const {
    return group_size_8_byte_.encoded_size() + wire::encoded_size_of(incremental_refresh_trade_summary_long_order_id_group_);
}

void IncrementalRefreshTradeSummaryLongOrderIdGroups::print(std::ostream& out) const {
    out << "IncrementalRefreshTradeSummaryLongOrderIdGroups{";
    out << "group_size_8_byte=";
    group_size_8_byte_.print(out);
    out << ", incremental_refresh_trade_summary_long_order_id_group=";
    print::sequence(out, incremental_refresh_trade_summary_long_order_id_group_);
    out << '}';
}

bool IncrementalRefreshTradeSummaryLongOrderIdGroups::operator==(const IncrementalRefreshTradeSummaryLongOrderIdGroups& other) const {
    return group_size_8_byte_ == other.group_size_8_byte_
        && incremental_refresh_trade_summary_long_order_id_group_ == other.incremental_refresh_trade_summary_long_order_id_group_;
}

bool IncrementalRefreshTradeSummaryLongOrderIdGroups::operator!=(const IncrementalRefreshTradeSummaryLongOrderIdGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const IncrementalRefreshTradeSummaryLongOrderIdGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
