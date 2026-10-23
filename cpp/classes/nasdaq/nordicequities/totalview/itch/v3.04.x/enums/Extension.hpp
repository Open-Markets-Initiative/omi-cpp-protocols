#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Whether the cross has been extended
enum class Extension : char {
    CrossExtension = 'E', // Cross Extension
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Extension value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Extension value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
