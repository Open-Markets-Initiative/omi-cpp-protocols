#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../groups/MarketDataRequestRelatedSymbolGroup.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

// NoRelatedSym Block
class MarketDataRequestRelatedSymbolGroups {
  public:

    MarketDataRequestRelatedSymbolGroups() = default;
    MarketDataRequestRelatedSymbolGroups(const GroupSize& group_size, const std::vector<MarketDataRequestRelatedSymbolGroup>& market_data_request_related_symbol_group);

    // Group Size: Repeating group dimensions
    const GroupSize& group_size() const;
    GroupSize& group_size();
    void set_group_size(const GroupSize& value);

    // Market Data Request Related Symbol Group: Number of instruments requested. When
    // NoSecurityGroups > 0 specified in the request, the NoRelatedSym should be equal 0
    const std::vector<MarketDataRequestRelatedSymbolGroup>& market_data_request_related_symbol_group() const;
    std::vector<MarketDataRequestRelatedSymbolGroup>& market_data_request_related_symbol_group();
    void set_market_data_request_related_symbol_group(const std::vector<MarketDataRequestRelatedSymbolGroup>& value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MarketDataRequestRelatedSymbolGroups& other) const;
    bool operator!=(const MarketDataRequestRelatedSymbolGroups& other) const;

  private:
    GroupSize group_size_{};
    std::vector<MarketDataRequestRelatedSymbolGroup> market_data_request_related_symbol_group_{};
};

std::ostream& operator<<(std::ostream& out, const MarketDataRequestRelatedSymbolGroups& value);

} // namespace cme::globex::mdp3::sbe::v1_8
