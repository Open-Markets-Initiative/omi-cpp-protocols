#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class BidOrdType : std::uint8_t {
    Market = 1, // Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BidOrdType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BidOrdType value);

} // namespace eurex::t7::eobi::fbe::v13_0
