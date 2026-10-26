#include "MarketDataRequestRelatedSymbolGroups.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

MarketDataRequestRelatedSymbolGroups::MarketDataRequestRelatedSymbolGroups(const GroupSize& group_size, const std::vector<MarketDataRequestRelatedSymbolGroup>& market_data_request_related_symbol_group)
  : group_size_(group_size), market_data_request_related_symbol_group_(market_data_request_related_symbol_group) {}

const GroupSize& MarketDataRequestRelatedSymbolGroups::group_size() const { return group_size_; }
GroupSize& MarketDataRequestRelatedSymbolGroups::group_size() { return group_size_; }
void MarketDataRequestRelatedSymbolGroups::set_group_size(const GroupSize& value) { group_size_ = value; }

const std::vector<MarketDataRequestRelatedSymbolGroup>& MarketDataRequestRelatedSymbolGroups::market_data_request_related_symbol_group() const { return market_data_request_related_symbol_group_; }
std::vector<MarketDataRequestRelatedSymbolGroup>& MarketDataRequestRelatedSymbolGroups::market_data_request_related_symbol_group() { return market_data_request_related_symbol_group_; }
void MarketDataRequestRelatedSymbolGroups::set_market_data_request_related_symbol_group(const std::vector<MarketDataRequestRelatedSymbolGroup>& value) { market_data_request_related_symbol_group_ = value; }

std::size_t MarketDataRequestRelatedSymbolGroups::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += group_size_.decode(data + offset, length - offset);

    {
        const std::size_t count = wire::count(group_size_.num_in_group());
        const std::size_t block = wire::count(group_size_.block_length());
        market_data_request_related_symbol_group_.clear();
        market_data_request_related_symbol_group_.reserve(count);
        for (std::size_t index = 0; index < count; ++index) {
            MarketDataRequestRelatedSymbolGroup entry;
            const std::size_t consumed = entry.decode(data + offset, length - offset);
            wire::require("MarketDataRequestRelatedSymbolGroups", offset + (block > consumed ? block : consumed), length);
            offset += block > consumed ? block : consumed;
            market_data_request_related_symbol_group_.push_back(std::move(entry));
        }
    }

    return offset;
}

std::size_t MarketDataRequestRelatedSymbolGroups::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MarketDataRequestRelatedSymbolGroups", encoded_size(), capacity);

    // Counts and lengths are written from what is encoded, not from what was stored
    auto group_size = group_size_;
    group_size.set_num_in_group(static_cast<std::uint8_t>(market_data_request_related_symbol_group_.size()));
    group_size.set_block_length(static_cast<std::uint16_t>(MarketDataRequestRelatedSymbolGroup::wire_size));

    offset += group_size.encode(data + offset, capacity - offset);

    for (const auto& entry : market_data_request_related_symbol_group_) {
        offset += entry.encode(data + offset, capacity - offset);
    }

    return offset;
}

std::size_t MarketDataRequestRelatedSymbolGroups::encoded_size() const {
    return group_size_.encoded_size() + wire::encoded_size_of(market_data_request_related_symbol_group_);
}

void MarketDataRequestRelatedSymbolGroups::print(std::ostream& out) const {
    out << "MarketDataRequestRelatedSymbolGroups{";
    out << "group_size=";
    group_size_.print(out);
    out << ", market_data_request_related_symbol_group=";
    print::sequence(out, market_data_request_related_symbol_group_);
    out << '}';
}

bool MarketDataRequestRelatedSymbolGroups::operator==(const MarketDataRequestRelatedSymbolGroups& other) const {
    return group_size_ == other.group_size_
        && market_data_request_related_symbol_group_ == other.market_data_request_related_symbol_group_;
}

bool MarketDataRequestRelatedSymbolGroups::operator!=(const MarketDataRequestRelatedSymbolGroups& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const MarketDataRequestRelatedSymbolGroups& value) {
    value.print(out);
    return out;
}

} // namespace cme::globex::mdp3::sbe::v1_13
