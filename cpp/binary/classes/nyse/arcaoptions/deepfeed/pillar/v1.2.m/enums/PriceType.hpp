// Nyse.ArcaOptions.DeepFeed.Pillar.v1.2.m: enums/PriceType.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Price type indicator.
enum class PriceType : std::uint8_t {
    StrikePriceIsDollarAmount = 0,  // Strike Price Is Dollar Amount
    StrikePriceIsPercentAmount = 1, // Strike Price Is Percent Amount
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceType value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
