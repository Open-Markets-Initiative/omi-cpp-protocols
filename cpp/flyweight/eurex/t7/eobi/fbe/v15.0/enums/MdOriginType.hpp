#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class MdOriginType : std::uint8_t {
    Book = 0,    // Book
    OffBook = 1, // Off Book
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdOriginType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdOriginType value);

} // namespace eurex::t7::eobi::fbe::v15_0
