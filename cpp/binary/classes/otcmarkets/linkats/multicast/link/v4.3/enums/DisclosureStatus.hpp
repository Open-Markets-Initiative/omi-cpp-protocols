#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Current disclosure status of the issuer.
enum class DisclosureStatus : std::uint8_t {
    NoDisclosure = 0,       // No Disclosure
    CurrentInformation = 2, // Current Information
    LimitedInformation = 3, // Limited Information
    NoInformation = 4,      // No Information
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(DisclosureStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, DisclosureStatus value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
