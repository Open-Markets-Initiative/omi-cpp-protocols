#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// ‘N’ = None ‘A’ = AON
enum class ExecFlag : char {
    None = 'N', // None
    Aon = 'A',  // Aon
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExecFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExecFlag value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
