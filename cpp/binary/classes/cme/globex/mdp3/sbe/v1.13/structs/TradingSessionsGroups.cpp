#include "TradingSessionsGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

TradingSessionsGroups::TradingSessionsGroups(const GroupSize& group_size, const std::vector<TradingSessionsGroup>& trading_sessions_group)
  : group_size_(group_size), trading_sessions_group_(trading_sessions_group) {}

const GroupSize& TradingSessionsGroups::group_size() const { return group_size_; }
GroupSize& TradingSessionsGroups::group_size() { return group_size_; }
void TradingSessionsGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<TradingSessionsGroup>& TradingSessionsGroups::trading_sessions_group() const { return trading_sessions_group_; }
std::vector<TradingSessionsGroup>& TradingSessionsGroups::trading_sessions_group() { return trading_sessions_group_; }
void TradingSessionsGroups::set_trading_sessions_group(const std::vector<TradingSessionsGroup>& value) { trading_sessions_group_ = value; }

std::size_t TradingSessionsGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        trading_sessions_group_.clear();
        trading_sessions_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            TradingSessionsGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("TradingSessionsGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            trading_sessions_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t TradingSessionsGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("TradingSessionsGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(trading_sessions_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(TradingSessionsGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : trading_sessions_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t TradingSessionsGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(trading_sessions_group_);
}

void TradingSessionsGroups::print(std::ostream& out) const {
    out << "TradingSessionsGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", trading_sessions_group=";
    print::sequence(out, trading_sessions_group_);
    out << '}';
}

bool TradingSessionsGroups::operator==(const TradingSessionsGroups& other) const {
    return group_size_ == other.group_size_
        && trading_sessions_group_ == other.trading_sessions_group_;
}

bool TradingSessionsGroups::operator!=(const TradingSessionsGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const TradingSessionsGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
