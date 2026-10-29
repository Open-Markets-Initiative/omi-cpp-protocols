#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Denotes whether the referenced transaction is to be cancelled or error
enum class CancelErrorAction : char {
    Cancel = '1', // Cancel
    Error = '2',  // Error
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CancelErrorAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CancelErrorAction value);

} // namespace siac::cts::output::cta::v2_10
