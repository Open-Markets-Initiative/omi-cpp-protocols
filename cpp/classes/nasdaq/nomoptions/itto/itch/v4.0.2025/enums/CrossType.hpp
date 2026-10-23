#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The NASDAQ auction session for which the message is being generated.
enum class CrossType : char {
    NasdaqOpeningReopening = 'O', // Nasdaq Opening Reopening
    PriceImprovement = 'P',       // Price Improvement
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
