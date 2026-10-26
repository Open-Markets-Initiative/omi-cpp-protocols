#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// The current SSR state, which this msg updates if the Security Status field contains an SSR
// Code. Valid
enum class SsrState : char {
    NoShortSaleRestrictionInEffect = '~', // No Short Sale Restriction In Effect
    ShortSaleRestrictionInEffect = 'E',   // Short Sale Restriction In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SsrState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SsrState value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
