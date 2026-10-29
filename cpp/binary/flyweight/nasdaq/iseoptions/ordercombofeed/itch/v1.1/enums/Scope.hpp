#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Scope value
enum class Scope : char {
    Local = 'L',    // Local
    National = 'N', // National
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Scope value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Scope value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
