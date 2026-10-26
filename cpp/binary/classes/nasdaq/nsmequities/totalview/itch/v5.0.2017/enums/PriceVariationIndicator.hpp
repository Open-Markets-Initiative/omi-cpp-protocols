#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// This field indicates the absolute value of the percentage of deviation of the Near
// Indicative Clearing Price to the nearest Current Reference Price.
enum class PriceVariationIndicator : char {
    Less = 'L',                                   // Less
    OneToOnePointNineNinePercent = '1',           // One To One Point Nine Nine Percent
    TwoToTwoPointNineNinePercent = '2',           // Two To Two Point Nine Nine Percent
    ThreeToThreePointNineNinePercent = '3',       // Three To Three Point Nine Nine Percent
    FourToFourPointNineNinePercent = '4',         // Four To Four Point Nine Nine Percent
    FiveToFivePointNineNinePercent = '5',         // Five To Five Point Nine Nine Percent
    SixToSixPointNineNinePercent = '6',           // Six To Six Point Nine Nine Percent
    SevenToSevenPointNineNinePercent = '7',       // Seven To Seven Point Nine Nine Percent
    EightToEightPointNineNinePercent = '8',       // Eight To Eight Point Nine Nine Percent
    NineToNinePointNineNinePercent = '9',         // Nine To Nine Point Nine Nine Percent
    TenToNineteenPointNineNinePercent = 'A',      // Ten To Nineteen Point Nine Nine Percent
    TwentyToTwentyNinePointNineNinePercent = 'B', // Twenty To Twenty Nine Point Nine Nine Percent
    ThirtyPercentOrGreater = 'C',                 // Thirty Percent Or Greater
    NoCalculation = ' ',                          // No Calculation
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceVariationIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceVariationIndicator value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
