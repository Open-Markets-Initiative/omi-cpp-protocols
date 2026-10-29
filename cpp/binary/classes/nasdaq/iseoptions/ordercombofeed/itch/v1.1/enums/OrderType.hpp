#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Order Type
enum class OrderType : char {
    Market = 'M', // Market
    Limit = 'L',  // Limit
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderType value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
