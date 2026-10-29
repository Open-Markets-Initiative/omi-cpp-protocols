#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Code identifying the primary listing market
enum class ListingMarket : char {
    Tsx = 'T',     // Tsx
    Venture = 'V', // Venture
    Cse = 'C',     // Cse
    Neo = 'N',     // Neo
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ListingMarket value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ListingMarket value);

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
