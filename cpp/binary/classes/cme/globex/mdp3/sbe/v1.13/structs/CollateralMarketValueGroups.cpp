#include "CollateralMarketValueGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

CollateralMarketValueGroups::CollateralMarketValueGroups(const GroupSize& group_size, const std::vector<CollateralMarketValueGroup>& collateral_market_value_group)
  : group_size_(group_size), collateral_market_value_group_(collateral_market_value_group) {}

const GroupSize& CollateralMarketValueGroups::group_size() const { return group_size_; }
GroupSize& CollateralMarketValueGroups::group_size() { return group_size_; }
void CollateralMarketValueGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<CollateralMarketValueGroup>& CollateralMarketValueGroups::collateral_market_value_group() const { return collateral_market_value_group_; }
std::vector<CollateralMarketValueGroup>& CollateralMarketValueGroups::collateral_market_value_group() { return collateral_market_value_group_; }
void CollateralMarketValueGroups::set_collateral_market_value_group(const std::vector<CollateralMarketValueGroup>& value) { collateral_market_value_group_ = value; }

std::size_t CollateralMarketValueGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        collateral_market_value_group_.clear();
        collateral_market_value_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            CollateralMarketValueGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("CollateralMarketValueGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            collateral_market_value_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t CollateralMarketValueGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("CollateralMarketValueGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(collateral_market_value_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(CollateralMarketValueGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : collateral_market_value_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t CollateralMarketValueGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(collateral_market_value_group_);
}

void CollateralMarketValueGroups::print(std::ostream& out) const {
    out << "CollateralMarketValueGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", collateral_market_value_group=";
    print::sequence(out, collateral_market_value_group_);
    out << '}';
}

bool CollateralMarketValueGroups::operator==(const CollateralMarketValueGroups& other) const {
    return group_size_ == other.group_size_
        && collateral_market_value_group_ == other.collateral_market_value_group_;
}

bool CollateralMarketValueGroups::operator!=(const CollateralMarketValueGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const CollateralMarketValueGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
