#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Indicates the primary listing market for the issue.
enum class SecurityClass : char {
    NasdaqListedIssue = 'Q', // Nasdaq Listed Issue
    Nyse = 'N',              // Nyse
    NyseAmerican = 'A',      // Nyse American
    NyseArca = 'P',          // Nyse Arca
    NyseTexas = 'M',         // Nyse Texas
    Bats = 'Z',              // Bats
    Iexg = 'V',              // Iexg
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityClass value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityClass value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
