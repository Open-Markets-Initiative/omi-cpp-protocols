#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// Significant Imbalance Values
enum class SignificantImbalance : char {
    Default = ' ',                          // Default
    TheCurrentImbalanceIsSignificant = 'Y', // The Current Imbalance Is Significant
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SignificantImbalance value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SignificantImbalance value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
