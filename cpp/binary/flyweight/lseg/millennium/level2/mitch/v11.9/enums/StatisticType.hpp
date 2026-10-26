#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// Statistic Type
enum class StatisticType : char {
    OpeningPrice = 'O', // Opening Price
    ClosingPrice = 'C', // Closing Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StatisticType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StatisticType value);

} // namespace lseg::millennium::level2::mitch::v11_9
