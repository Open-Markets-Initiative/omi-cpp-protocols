#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Value is ‘O’ for OPRA
enum class DataFeedIndicator : char {
    Opra = 'O', // Opra
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(DataFeedIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, DataFeedIndicator value);

} // namespace siac::opra::output::obi::v6_2
