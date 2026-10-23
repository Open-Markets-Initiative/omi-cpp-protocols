#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Open Interest Message Type
enum class OpenInterestMessageType : char {
    OpenInterest = ' ', // Open Interest
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpenInterestMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpenInterestMessageType value);

} // namespace siac::opra::output::obi::v6_2
